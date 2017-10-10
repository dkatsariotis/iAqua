// Set default EEPROM values
//firstRunSetup();

void readPowerSchedule() // Load power schedule from eeprom
{

  ledEn.En = EEPROM.read(327);
  lights.onHour = EEPROM.read(328);
  lights.onMinute = EEPROM.read(330);
  lights.offHour = EEPROM.read(329);
  lights.offMinute = EEPROM.read(331);

  co2En.En = EEPROM.read(332);
  co2.onHour = EEPROM.read(333);
  co2.onMinute = EEPROM.read(335);
  co2.offHour = EEPROM.read(334);
  co2.offMinute = EEPROM.read(336);

  circEn.En = EEPROM.read(337);
  circ.onHour = EEPROM.read(338);
  circ.onMinute = EEPROM.read(340);
  circ.offHour = EEPROM.read(339);
  circ.offMinute = EEPROM.read(341);

}

void readDosingSchedule() // Load dosing schedule from eeprom
{

  pump1.onHour = EEPROM.read(300);
  pump1.onMinute = EEPROM.read(301);
  pump1.Sun = EEPROM.read(302);
  pump1.Mon = EEPROM.read(303);
  pump1.Tue = EEPROM.read(304);
  pump1.Wed = EEPROM.read(305);
  pump1.Thu = EEPROM.read(306);
  pump1.Fri = EEPROM.read(307);
  pump1.Sat = EEPROM.read(308);

  pump2.onHour = EEPROM.read(309);
  pump2.onMinute = EEPROM.read(310);
  pump2.Sun = EEPROM.read(311);
  pump2.Mon = EEPROM.read(312);
  pump2.Tue = EEPROM.read(313);
  pump2.Wed = EEPROM.read(314);
  pump2.Thu = EEPROM.read(315);
  pump2.Fri = EEPROM.read(316);
  pump2.Sat = EEPROM.read(317);

  pump3.onHour = EEPROM.read(318);
  pump3.onMinute = EEPROM.read(319);
  pump3.Sun = EEPROM.read(320);
  pump3.Mon = EEPROM.read(321);
  pump3.Tue = EEPROM.read(322);
  pump3.Wed = EEPROM.read(323);
  pump3.Thu = EEPROM.read(324);
  pump3.Fri = EEPROM.read(325);
  pump3.Sat = EEPROM.read(326);

}

void smartStartup()
{

  RTC.now();

  int onHour, offHour, onHour2, offHour2, onHour3, offHour3;

  onHour = hour() - UTC_Offset;
  time_t currentStamp = tmConvert_t(year(), month(), day(), onHour, minute(), second());

  /*  Serial.print("currentStamp: ");
    Serial.print(currentStamp);
    Serial.print("\n");
  */

  //  AlarmPwrFan_Off(); // Fan is always off at startup
  //  AlarmPwrHeater_Off(); // Heater is always off at startup
  //  AlarmPwrLights_Off(); // Lights always off at startup
  //  AlarmPwrCO2_Off(); // CO2 always off at startup
  //  AlarmPwrCirc_Off(); // Circ always off at startup

  // Lights Power On
  // read in the power schedule and see if we are at a time when it should be on
  onHour = lights.onHour - UTC_Offset; // adjust for time zone
  offHour = lights.offHour - UTC_Offset; // adjust for time zone
  time_t powerOn = tmConvert_t(year(), month(), day(), onHour, lights.onMinute, 0); // get a unix time stamp for the power on
  time_t powerOff = tmConvert_t(year(), month(), day(), offHour, lights.offMinute, 0); // get a unix time stamp for the power off

  if (ledEn.En)
  {
    if (powerOff < powerOn) // if something turns off after midnight, then we only consider power on time
    {
      if (powerOn <= currentStamp) AlarmPwrLights_On(); // turn on power if it's past power on time
    }
    else if ((powerOn <= currentStamp) && (powerOff > currentStamp)) // turn on power if it's within the window
    {
      AlarmPwrLights_On(); // turn on power if it's within the window
    }
  }


  // CO2 Power On
  // read in the power schedule and see if we are at a time when it should be on
  onHour = co2.onHour - UTC_Offset; // adjust for time zone
  offHour = co2.offHour - UTC_Offset; // adjust for time zone
  powerOn = tmConvert_t(year(), month(), day(), onHour, co2.onMinute, 0); // get a unix time stamp for the power on
  powerOff = tmConvert_t(year(), month(), day(), offHour, co2.offMinute, 0); // get a unix time stamp for the power off
  if (co2En.En)
  {
    if (powerOff < powerOn) // if something turns off after midnight, then we only consider power on time
    {
      if (powerOn <= currentStamp) AlarmPwrCO2_On(); // turn on power if it's past power on time
    }
    else if ((powerOn <= currentStamp) && (powerOff > currentStamp)) // turn on power if it's within the window
    {
      AlarmPwrCO2_On(); // turn on power if it's within the window
    }
  }



  // Circ Power On
  // read in the power schedule and see if we are at a time when it should be on
  onHour = circ.onHour - UTC_Offset; // adjust for time zone
  offHour = circ.offHour - UTC_Offset; // adjust for time zone
  powerOn = tmConvert_t(year(), month(), day(), onHour, circ.onMinute, 0); // get a unix time stamp for the power on
  powerOff = tmConvert_t(year(), month(), day(), offHour, circ.offMinute, 0); // get a unix time stamp for the power off
  if (circEn.En)
  {
    if (powerOff < powerOn) // if something turns off after midnight, then we only consider power on time
    {
      if (powerOn <= currentStamp) AlarmPwrCirc_On(); // turn on power if it's past power on time
    }
    else if ((powerOn <= currentStamp) && (powerOff > currentStamp)) // turn on power if it's within the window
    {
      AlarmPwrCirc_On(); // turn on power if it's within the window
    }
  }

}















