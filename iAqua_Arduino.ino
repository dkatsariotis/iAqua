#include <Wire.h>
#include <OneWire.h>
#include <EEPROMex.h>
#include <UTFT.h>
#include <UTouch.h>
#include <SdFat.h>
#include <UTFT_SdRaw.h>
#include <RTClib.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <DallasTemperature.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Define SD card file system
SdFat sd;


// Web Section start
// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFE };
IPAddress server_addr("mySQL Server Address");
//DNSClient dns1;
EthernetClient client;
MySQL_Connection conn((Client *)&client);
MySQL_Cursor cur = MySQL_Cursor(&conn);
char user[] = "mySQL User Name";
char password[] = "mySQL Password";

char INSERT_DATA[] = "INSERT INTO iAqua.data (temp, date, time, sync) VALUES (%s,%s,%s,0)";
char UPDATE_CONTROL[] = "UPDATE iAqua.control SET lights=%i, co2=%i, fan=%i, heater=%i, tempset=%i, tank1=%i, tank2=%i, tank3=%i";
char SELECT_CONTROL_CMD[] = "SELECT * FROM iAqua.control_cmd";
char UPDATE_CONTROL_CMD[] = "UPDATE iAqua.control_cmd SET lightsval=false, co2val=false, fanval=false, heaterval=false, cmd=false";

char query[128];
char ddate[128];
char ttime[128];

boolean LightsStatus = false;
boolean CO2Status = false;
boolean FanStatus = false;
boolean HeaterStatus = false;
boolean CircStatus = false;
// Web Section end


// Declare which fonts we will be using
extern uint8_t f_sinclair_S[];
extern uint8_t f_arial_bold[];


// Define pins
#define pwrFanPin A6  //Cooling fan relay
#define pump1Pump A7  //Pump 1 relay
#define pump2Pump A9  //Pump 2 relay
#define pump3Pump A10  //Pump 3 relay
#define pwrCircPin A11  //Lights relay
#define pwrCO2Pin A12  //CO2 Relay
#define pwrLightsPinLED A13  //LED relay
#define pwrHeaterPin A14  //Heater relay
#define screenBrightPin 8  // LCD back light pin
#define lightSensorPin A8  // Light sensor pin
#define ONE_WIRE_BUS 9  // Temperature sensor


// Set startup values
byte backLight = 255;  // Set brightness to 100%
boolean backlightTouch = true; // Allow the screen to stay bright after boot
// STC run timestamp
unsigned long stctime;

// Set Home screen
byte dispScreen = 1;

// Set Web section value
byte web = 0;

// Set schedule item
byte scheduleItem;

// Time update
boolean updateTime = true;

// Screen settings corresponding to eeprom values 28-31
byte screenRetHome, screenDimLevel, screenDimSec, screenBrightMem;

// oneWire instance to communicate with OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);


// Time define
RTC_DS3231 RTC;
byte UTC_Offset = +3; // Time zone


// Touch and SD card pins
UTFT myGLCD(SSD1289, 38, 39, 40, 41); // SD card Pins
UTouch myTouch(46, 45, 44, 43, 42);   //Touch pins


// Instance to read images from SD card
UTFT_SdRaw myFiles(&myGLCD);

// Large power buttons for the power screen off and on
char *pwrFanIcon[] = {
  "3fan_F.raw", "3fan_N.raw"
};
char *pwrLightIcon[] = {
  "3light_F.raw", "3light_N.raw"
};
char *pwrCircIcon[] = {
  "3circ_F.raw", "3circ_N.raw"
};
char *pwrLight2Icon[] = {
  "3light_F.raw", "3light_N.raw"
};
char *pwrLight3Icon[] = {
  "3light_F.raw", "3light_N.raw"
};
char *pwrCO2Icon[] = {
  "3co2_F.raw", "3co2_N.raw"
};
char *pwrHeatIcon[] = {
  "3heat_F.raw", "3heat_N.raw"
};


// On off power dot under each power button on the power screen
char *pwrDot[] = {
  "3dotR.raw", "3dotG.raw"
};


// Small power icons for the home screen  off and on
char *pwrFanIconS[] = {
  "1fanF.raw", "1fanN.raw"
};
char *pwrHeatIconS[] = {
  "1heatF.raw", "1heatN.raw"
};
char *pwrCircIconS[] = {
  "1circF.raw", "1circN.raw"
};
char *pwrLightIconS[] = {
  "1lightF.raw", "1lightN.raw"
};
char *pwrLight2IconS[] = {
  "1lightF.raw", "1lightN.raw"
};
char *pwrLight3IconS[] = {
  "1lightF.raw", "1lightN.raw"
};
char *pwrCO2IconS[] = {
  "1co2F.raw", "1co2N.raw"
};


// 24 pixel up and down arrow buttons
char *arrowButton[] = {
  "24whUp.raw", "24whDn.raw"
};


// Enabled or disabled large check boxes
char *schedActiveB[] = {
  "15disB.raw", "15enabB.raw"
};


// Days and month character strings for displaying at the top of the screen
char *Day[] = {
  "", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};
char *Mon[] = {
  "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};


// Used for time
struct RTC_T
{
  int tHour;
  int tMinute;
  int tSecond;
  int tDow;
  int tDay;
  int tMonth;
  int tYear;
}
tmpRTC, prevRTC, saveRTC;


// Used for storing power states of relays
struct PWR
{
  boolean pwrFan;
  boolean pwrHeater;
  boolean pwrLights;
  boolean pwrCirc;
  boolean pwrCO2;
  boolean En;
}
globalPower;


struct LIGHTSSCHED
{
  byte onHour;
  byte onMinute;
  byte offHour;
  byte offMinute;
  boolean En;
}
lights, ledEn;


struct CIRCSCHED
{
  byte onHour;
  byte onMinute;
  byte offHour;
  byte offMinute;
  boolean En;
}
circ, circEn;


struct CO2SCHED
{
  byte onHour;
  byte onMinute;
  byte offHour;
  byte offMinute;
  boolean En;
}
co2, co2En;


// Holds the scheduling for 3 dosing pumps
struct PUMPSCHED
{
  byte onHour;
  byte onMinute;
  byte Sun;
  byte Mon;
  byte Tue;
  byte Wed;
  byte Thu;
  byte Fri;
  byte Sat;
}
pump1, pump2, pump3;


int x, y; // Touch coordinates


// Various Global Vars
//Dosing
float doses1, doses2, doses3;
float doseAmt1, doseAmt2, doseAmt3;
byte doseCap1, doseCap2, doseCap3;
float vol1, vol2, vol3;

//Pump
int pumpTime1, pumpTime2, pumpTime3;

//Temp
int intTempC, STC, STCTemp;

//Web
int STCTempInt;
byte doses1Int, doses2Int, doses3Int;
byte heaterval, fanval, co2val, lightsval;
boolean cmd;
boolean webbypass = false;

//Dosing scheduler
byte DoseSchHour, DoseSchMin, daySun, dayMon, dayTue, dayWed, dayThu, dayFri, daySat;
byte DoseHour, DoseMinute;

//Lights scheduler
byte LightsSchHour, LightsSchMin, LightsEnabled;
byte LightsHour, LightsMinute;

//CO2 scheduler
byte Co2SchHour, Co2SchMin;
boolean Co2Enabled;
byte Co2Hour, Co2Minute;

//Circ scheduler
byte CircSchHour, CircSchMin, CircEnabled;
byte CircHour, CircMinute;

// Various millis to keep track of
unsigned long prevMillisTouch = 0; // Track time between touches
unsigned long prevMillis5sec = 0; // Track seconds for refreshing clock and temp
unsigned long prevMillisSQLRead = 0; // Track seconds for reading from mySQL
unsigned long prevMillisSQLUpdate = 0; // Track seconds for comiting to mySQL
unsigned long millisDim = 0; // Used for brightness adjustment
unsigned long millisHome = 0; // Used for returning home after configured time


float tempC = 0;  // Water temperature
char tempstring[7];  // Water temperature as a string


int freeRam ()
{
  // Returns available SRAM
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}


void setup()
{

  Serial.begin(115200);

  EEPROM.setMaxAllowedWrites(600);

  // Initiate screen and touch
  myGLCD.InitLCD(PORTRAIT);
  myTouch.InitTouch(PORTRAIT);
  myTouch.setPrecision(PREC_MEDIUM);


  // Initiate SD card
  sd.begin(53, SPI_FULL_SPEED);

  Wire.begin();
  RTC.begin();

  delay(250);

  setSyncProvider(syncProvider);


  // Set all pin modes for outputs and inputs and keeps Relays Off
  pinMode(pwrFanPin, OUTPUT);
  digitalWrite(pwrFanPin, HIGH);
  pinMode(pwrCircPin, OUTPUT);
  digitalWrite(pwrCircPin, HIGH);
  pinMode(pwrLightsPinLED, OUTPUT);
  digitalWrite(pwrLightsPinLED, HIGH);
  pinMode(pwrHeaterPin, OUTPUT);
  digitalWrite(pwrHeaterPin, HIGH);
  pinMode(pwrCO2Pin, OUTPUT);
  digitalWrite(pwrCO2Pin, HIGH);
  pinMode(screenBrightPin, OUTPUT);
  pinMode(lightSensorPin, INPUT);
  pinMode(pump1Pump, OUTPUT);
  digitalWrite(pump1Pump, HIGH);
  pinMode(pump2Pump, OUTPUT);
  digitalWrite(pump2Pump, HIGH);
  pinMode(pump3Pump, OUTPUT);
  digitalWrite(pump3Pump, HIGH);

  // Start sensors
  sensors.begin(); // Start up temperature library
  sensors.setResolution(9); //Set temp resolution


  // Get screen settings from EEPROM
  screenRetHome = EEPROM.read(28);
  screenDimLevel = EEPROM.read(29);
  screenDimSec = EEPROM.read(30);
  screenBrightMem = EEPROM.read(31);


  // Get fan operation temp from EEPROM
  STCTemp = EEPROM.read(18);

  analogWrite(screenBrightPin, screenBrightMem); // Turn up screen brightness right away

  // Ethernet shield
  // disable Ethernet chip
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  // disable SD card
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  Serial.println(F("Initializing Ethernet"));
  Ethernet.begin(mac);  // initialize Ethernet device
  Serial.print(F("IP Address: "));
  Serial.println(Ethernet.localIP());
  Serial.print(F("Subnet Mask: "));
  Serial.println(Ethernet.subnetMask());
  Serial.print(F("DNS: "));
  Serial.println(Ethernet.dnsServerIP());
  Serial.print(F("Gateway: "));
  Serial.println(Ethernet.gatewayIP());
  //  dns1.begin(Ethernet.dnsServerIP());
  Serial.print(F("mySQL Server IP: "));
  Serial.println(server_addr);

  Serial.println(F("Connecting to MySQL..."));
  conn.connect(server_addr, 3306, user, password); // Connect to MySQL

  readDosingSchedule(); // Read the dosing schedule

  readPowerSchedule(); // Read power schedule

  myGLCD.clrScr();


  // Boot up logo
  //  myFiles.load(26, 80, 188, 72, "iAqua.raw");
  delay(1000);


  updateAlarms(); // Create all alarms


  myGLCD.clrScr();


  updateTimeDate(); // Update time and date


  screenHome(); // Display home screen


  smartStartup(); // Start up all power and set lighting mode according to schedule


  // Update millis to keep screen bright
  millisDim = millis();

}

time_t syncProvider()
{
  return RTC.now().unixtime();
}


void loop()
{

  unsigned long currentMillis = millis(); // Get current millis

  // Check for touch events
  if (myTouch.dataAvailable())  {
    //    if (currentMillis - prevMillisTouch > 500) // Make sure it's been .5 sec between touches
    if (currentMillis - prevMillisTouch > 150)
    {
      // Set back light touch if not already set and turn up brightness
      if (backlightTouch == false) // Back light touch is for adjusting brightness after touch
      {
        backLight = 255;
        analogWrite(screenBrightPin, backLight);
        backlightTouch = true;
      }

      prevMillisTouch = currentMillis; // Reset the touch timer
      millisDim = currentMillis; // Reset screen dim timer
      millisHome = currentMillis; // Reset return home timer

      processMyTouch();
    }
  }
  // Update time and temp every 10 seconds
  if (currentMillis - prevMillis5sec > 10000)
  {
    prevMillis5sec = millis();
    updateTimeDate();
    if (dispScreen == 1) checkTemp();
  }


  // Check mySQL cmd every 1 minutes
  if (currentMillis - prevMillisSQLRead > 60000)
  {
    prevMillisSQLRead = millis();
    web = 2;
    websection();
  }

  // Update mySQL data every ~5 minutes
  if (currentMillis - prevMillisSQLUpdate > 301700)
  {
    prevMillisSQLUpdate = millis();
    web = 1;
    websection();
  }

  // Adjust brightness automatically unless touch event
  if (screenDimSec != 0) // If set to 0, we won't dim
  {
    if (screenDimLevel != 0) // If set to 0, we won't dim
    {
      if (backlightTouch == true)
      {
        unsigned long pastMillis = (currentMillis - millisDim);
        if (pastMillis > (1000 * screenDimSec)) backlightTouch = false;
      }
      else
      {
        autoBrightness();
      }
    }
  }

  // If we aren't on the home screen, we return after preset time of no interaction
  if (screenRetHome != 0) // If set to 0, we don't return home
  {
    if (dispScreen != 1)
    {
      unsigned long pastMillis = (currentMillis - millisHome);
      if (pastMillis > (60000 * screenRetHome))
      {
        if (dispScreen == 9)
        {
          updateAlarms(); // This will rebuild all of the schedules
          smartStartup(); // Apply Alarms
        }
        screenHome();
      }
    }
  }

  // Get time in seconds (since 1970)
  unsigned long rightNow = now();

  Alarm.delay(6); // Must use Alarm delay to use the TimeAlarms library

}

void SaveTime()
{
  saveRTC.tYear = (saveRTC.tYear + 2000);
  RTC.adjust(DateTime(saveRTC.tYear, saveRTC.tMonth, saveRTC.tDay, saveRTC.tHour, saveRTC.tMinute, saveRTC.tSecond));
  Serial.println(F("Time set"));
  updateTimeDate();
}

void updateTimeDate()
{

  RTC.now();

  // Draw date and time
  myGLCD.setColor(240, 240, 255);
  myGLCD.setFont(f_sinclair_S);

  if ((hour() != prevRTC.tHour) || (minute() != prevRTC.tMinute) || updateTime) printTime(hour(), minute(), 196, 4); // Time

  if ((day() != prevRTC.tDay) || (month() != prevRTC.tMonth) || (year() != prevRTC.tYear) || updateTime) // Date
  {
    prevRTC.tDay = day();
    prevRTC.tMonth = month();
    printDate(40, 2);
  }
}

void printTime(int thour, int tminute, int posx, int posy)
{
  char tmpTime[8], charT[3];

  tmpTime[0] = '\0';

  if (thour >= 0 && thour <= 9) // Add space
  {
    strcat(tmpTime, " ");
    itoa(thour, charT, 10);
    strcat(tmpTime, charT);
  }
  else
    itoa(thour, tmpTime, 10);

  strcat(tmpTime, ":");

  if (tminute >= 0 && tminute <= 9) // Add 0
  {
    strcat(tmpTime, "0");
    itoa(tminute, charT, 10);
    strcat(tmpTime, charT);
  }
  else {
    itoa(tminute, charT, 10);
    strcat(tmpTime, charT);
  }
  myGLCD.print(tmpTime, posx, posy); // Display time
}

void printDate(int x, int y)
{
  char  chDate[25], tmpChar[5];

  strcat(chDate, "     ");
  chDate[0] = '\0';
  strcat(chDate, Day[weekday()]);
  strcat(chDate, ", ");
  strcat(chDate, Mon[month()]);
  strcat(chDate, " ");
  itoa(day(), tmpChar, 10);
  strcat(chDate, tmpChar);
  strcat(chDate, " ");

  myGLCD.print(chDate, x, y); // Display date
}

time_t tmConvert_t(int YYYY, byte MM, byte DD, byte hh, byte mm, byte ss)
{
  tmElements_t tmSet;
  tmSet.Year = YYYY - 1970;
  tmSet.Month = MM;
  tmSet.Day = DD;
  tmSet.Hour = hh;
  tmSet.Minute = mm;
  tmSet.Second = ss;
  return makeTime(tmSet); // Convert to time_t
}

void autoBrightness()
{

  int photocellReading = analogRead(lightSensorPin);

  // Map the photo sensor value of 0-1023 directly to the PWM output of 0-255
  int brightnessLevel = map(photocellReading, 0, 1023, 0, 255);

  // Apply a brightness bump or drop based on the user preference auto dim setting
  int brightAdjust;
  if (screenDimLevel == 1) brightAdjust = -20;
  else if (screenDimLevel == 2) brightAdjust = -10;
  else if (screenDimLevel == 3) brightAdjust = 0;
  else if (screenDimLevel == 4) brightAdjust = 10;
  else if (screenDimLevel == 5) brightAdjust = 20;

  brightnessLevel = brightnessLevel + brightAdjust; // Apply brightness adjustment
  if (brightnessLevel > 255) brightnessLevel = 255; // Can't get brighter than 255
  if (brightnessLevel < 2) brightnessLevel = 1; // Must be at least 1 or it's off

  int diff = brightnessLevel - backLight;
  if (diff < 0)
  {
    diff = ((diff - diff) - diff);
  }
  if (diff > 25) // We only adjust brightness if it's more than a 10% change from where we are now
  {
    rampScreenBrightness(backLight, brightnessLevel);
  }

}

// Smoothly ramps the screen brightness from one level to another
void rampScreenBrightness(byte fromLevel, byte toLevel)
{
  if (fromLevel < toLevel)
  {
    while (fromLevel < toLevel)
    {
      analogWrite(screenBrightPin, fromLevel);
      fromLevel++;
      delay(5);
    }
  }
  else if (fromLevel > toLevel)
  {
    while (fromLevel > toLevel)
    {
      analogWrite(screenBrightPin, fromLevel);
      fromLevel--;
      delay(5);
    }
  }
  backLight = toLevel;
}


void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
  asm volatile ("  jmp 0");
}





















