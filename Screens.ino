void screenHome()  // Draw home screen showing overview info
{

  if (dispScreen != 1)   myGLCD.clrScr(); // Clear if not home

  dispScreen = 1; // Set home screen

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(0, 32, 239, 254); // Clear the screen between the header and the dock

  // Draw dock, home icon, and header
  myFiles.load(0, 254, 240, 66, "dock.raw");
  myFiles.load(2, 2, 30, 30, "1home.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(34, 81, 255);
  myGLCD.print("iAqua       ", 36, 12);

  // Draw lines to divide screen
  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header
  myGLCD.drawLine(0, 110, 239, 110); // Across screen below temp
  myGLCD.drawLine(105, 110, 105, 253); // 1st cutting into 4ths
  myGLCD.drawLine(168, 110, 168, 253); // 2nd cutting into 4ths

  // myGLCD.drawLine(105, 110, 105, 237); // 1st cutting into 4ths
  // myGLCD.drawLine(168, 110, 168, 237); // 2nd cutting into 4ths
  // myGLCD.drawLine(0, 237, 239, 237); // Across above dock

  // Draw water temp logo
  myFiles.load(50, 44, 60, 51, "1therm.raw");

  //checkTemp(); // Check temp and draw to screen

  myFiles.load(202, 66, 14, 12, "c.raw");

  checkDosing(); // Get remaining doses

  // Draw power status of outputs
  myFiles.load(178, 121, 24, 24, pwrLightIconS[globalPower.pwrLights]);
  myFiles.load(178, 155, 24, 24, pwrFanIconS[globalPower.pwrFan]);
  myFiles.load(178, 189, 24, 24, pwrHeatIconS[globalPower.pwrHeater]);
  myFiles.load(206, 121, 24, 24, pwrCircIconS[globalPower.pwrCirc]);
  myFiles.load(206, 155, 24, 24, pwrCO2IconS[globalPower.pwrCO2]);

}

void screenPower()  // Power control screen
{

  dispScreen = 3;

  myGLCD.clrScr();

  // Draw footer
  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer
  myFiles.load(107, 294, 26, 26, "foothome.raw");
  updateTimeDate();

  // Draw header
  myFiles.load(2, 2, 30, 30, "3power.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(222, 8, 51);
  myGLCD.print("POWER      ", 36, 12);

  myGLCD.setColor(255, 255, 255);
  myGLCD.print("MASTER", CENTER, 52);

  // On and off buttons
  myFiles.load(73, 77, 40, 40, "3allon.raw");
  myFiles.load(128, 77, 40, 40, "3alloff.raw");

  // Power icons and power dots
  myFiles.load(15, 212, 48, 48, pwrFanIcon[globalPower.pwrFan] );
  myFiles.load(34, 264, 10, 11, pwrDot[globalPower.pwrFan]);
  myFiles.load(15, 139, 48, 48, pwrLightIcon[globalPower.pwrLights]);
  myFiles.load(34, 192, 10, 11, pwrDot[globalPower.pwrLights]);
  myFiles.load(69, 212, 48, 48, pwrCO2Icon[globalPower.pwrCO2] );
  myFiles.load(88, 264, 10, 11, pwrDot[globalPower.pwrCO2]);
  myFiles.load(69, 139, 48, 48, pwrCircIcon[globalPower.pwrCirc] );
  myFiles.load(88, 192, 10, 11, pwrDot[globalPower.pwrCirc]);
  myFiles.load(123, 139, 48, 48, pwrHeatIcon[globalPower.pwrHeater]);
  myFiles.load(142, 192, 10, 11, pwrDot[globalPower.pwrHeater]);
  myFiles.load(181, 212, 48, 63, "reset.raw");

}

void screenSettings()  // Settings screen
{
  dispScreen = 4;

  myGLCD.clrScr();

  // Draw header
  myFiles.load(2, 2, 30, 30, "4extras.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print("SETTINGS  ", 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer

  myFiles.load(107, 294, 26, 26, "foothome.raw");  // Footer home button

  // Draw buttons

  myFiles.load(10, 50, 48, 63, "4clock.raw");
  myFiles.load(67, 50, 48, 63, "4screen.raw");
  myFiles.load(124, 50, 48, 63, "4heater.raw");
  myFiles.load(181, 50, 48, 63, "4dosing.raw");
  myFiles.load(10, 118, 48, 63, "4test.raw");
  myFiles.load(67, 118, 48, 63, "4fill.raw");

}

void screenCO2(byte CO2screen) // CO2 scheduling screen, screen draws based on CO2 Status
{

  dispScreen = 18;
  myGLCD.clrScr();

  char char3[3];
  char char3t[3];

  scheduleItem = CO2screen; // Track which status of CO2 we are editing

  // Draw header
  myFiles.load(2, 2, 30, 30, "18co2.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print("CO2 DOSING", 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer
  myFiles.load(107, 294, 26, 26, "footschd.raw");

  // CO2 On, CO2 Off buttons to swap schedules
  myFiles.load(12, 71, 46, 22, "3on.raw");
  myFiles.load(12, 120, 46, 22, "3off.raw");


  myGLCD.drawLine(70, 70, 70, 170); // Separate line

  myGLCD.setColor(255, 255, 255);

  // Based on pump selected, get the schedule
  if (CO2screen == 1)
  {
    myGLCD.setColor(0, 255, 0);  // Green for CO2 On
    myGLCD.print("CO2 On", 85, 70);
    Co2SchHour = co2.onHour;
    Co2SchMin = co2.onMinute;
  }
  if (CO2screen == 2)
  {
    myGLCD.setColor(255, 0, 0);  // Red for CO2 Off
    myGLCD.print("CO2 Off", 85, 70);
    Co2SchHour = co2.offHour;
    Co2SchMin = co2.offMinute;
  }

  // Convert schedule to char and print
  itoa(Co2SchHour, char3, 10);
  if (Co2SchHour >= 0 && Co2SchHour <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 120, 129);

  itoa(Co2SchMin, char3, 10);
  if (Co2SchMin >= 0 && Co2SchMin <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 199, 129);

  // Buttons to set time
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("H", 93, 93);
  myFiles.load(85, 110, 24, 24, arrowButton[0]);
  myFiles.load(85, 140, 24, 24, arrowButton[1]);
  myGLCD.print("M", 172, 93);
  myFiles.load(164, 110, 24, 24, arrowButton[0]);
  myFiles.load(164, 140, 24, 24, arrowButton[1]);

  // Enabled check box
  if (CO2screen == 1)
  {
    Co2Enabled = co2En.En;
    myGLCD.print("Enabled", 38, 192);
    myFiles.load(51, 203, 30, 30, schedActiveB[Co2Enabled]);
  }
}

void screenScreen() // Screen settings screen
{

  dispScreen = 16;
  char char3[3]; // Used to convernt numbers to char
  char char4[4];

  myGLCD.clrScr();

  // Draw header
  myFiles.load(2, 2, 30, 30, "16screen.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print("SCREEN", 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header

  // 3 horizontal separate lines
  myGLCD.drawLine(0, 102, 239, 102);
  myGLCD.drawLine(0, 170, 239, 170);
  myGLCD.drawLine(0, 238, 239, 238);

  // Draw return home labels
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("RETURN", 4, 49);
  myGLCD.print("TO HOME", 4, 70);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("AFTER LAST TOUCH", 8, 90);

  // Return to home up/down buttons
  myFiles.load(145, 42, 24, 24, arrowButton[0]);
  myFiles.load(145, 72, 24, 24, arrowButton[1]);

  // Draw return home setting
  myGLCD.setFont(f_arial_bold);
  itoa(screenRetHome, char3, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char3, 191, 59);

  // Auto dim labels
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("AUTO-DIM", 4, 112);
  myGLCD.print("LEVEL", 4, 133);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("0 TO 5 (0=OFF)", 6, 154);

  // Auto dim up/down
  myFiles.load(145, 110, 24, 24, arrowButton[0]);
  myFiles.load(145, 140, 24, 24, arrowButton[1]);

  // Auto dim setting
  itoa(screenDimLevel, char3, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(f_arial_bold);
  myGLCD.print(char3, 191, 127);

  // Auto dim seconds labels
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("AUTO-DIM", 4, 181);
  myGLCD.print("SECONDS", 4, 202);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("AFTER LAST TOUCH", 6, 223);

  // Auto dim seconds up/down
  myFiles.load(145, 178, 24, 24, arrowButton[0]);
  myFiles.load(145, 208, 24, 24, arrowButton[1]);

  // Auto dim seconds setting
  itoa(screenDimSec, char4, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(f_arial_bold);
  myGLCD.print(char4, 191, 197);

  // Brightness labels
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("BRIGHT", 4, 249);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("IF NOT USING", 6, 270);
  myGLCD.print("AUTO-DIM", 6, 283);

  // Brightness up/down
  myFiles.load(145, 245, 24, 24, arrowButton[0]);
  myFiles.load(145, 275, 24, 24, arrowButton[1]);

  // Brightness setting
  itoa(screenBrightMem, char4, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(f_arial_bold);
  myGLCD.print(char4, 187, 264);

  // Labels under each setting
  myGLCD.setFont(f_sinclair_S);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("MIN", 195, 83);
  myGLCD.print("3 AVG", 187, 151);
  myGLCD.print("SEC", 195, 221);
  myGLCD.print("1-255", 187, 288);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw");

}

void screenLights(byte Lightsscreen) // Lights scheduling screen, screen draws based on lights Status
{

  dispScreen = 17;
  myGLCD.clrScr();

  char char3[3];
  char char3t[3];

  scheduleItem = Lightsscreen; // Track which status of lights we are editing

  // Draw header
  myFiles.load(2, 2, 30, 30, "17led.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print("LIGHTING", 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer
  myFiles.load(107, 294, 26, 26, "footschd.raw");

  // Lights On, Lights Off buttons to swap schedules
  myFiles.load(12, 71, 46, 22, "3on.raw");
  myFiles.load(12, 120, 46, 22, "3off.raw");


  myGLCD.drawLine(70, 70, 70, 170); // Separate line

  myGLCD.setColor(255, 255, 255);

  // Based on pump selected, get the schedule
  if (Lightsscreen == 1)
  {
    myGLCD.setColor(0, 255, 0);  // Green for Lights On
    myGLCD.print("LED On", 85, 70);
    LightsSchHour = lights.onHour;
    LightsSchMin = lights.onMinute;
  }
  if (Lightsscreen == 2)
  {
    myGLCD.setColor(255, 0, 0);  // Red for Lights Off
    myGLCD.print("LED Off", 85, 70);
    LightsSchHour = lights.offHour;
    LightsSchMin = lights.offMinute;
  }

  // Convert schedule to char and print
  itoa(LightsSchHour, char3, 10);
  if (LightsSchHour >= 0 && LightsSchHour <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 120, 129);

  itoa(LightsSchMin, char3, 10);
  if (LightsSchMin >= 0 && LightsSchMin <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 199, 129);

  // Buttons to set time
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("H", 93, 93);
  myFiles.load(85, 110, 24, 24, arrowButton[0]);
  myFiles.load(85, 140, 24, 24, arrowButton[1]);
  myGLCD.print("M", 172, 93);
  myFiles.load(164, 110, 24, 24, arrowButton[0]);
  myFiles.load(164, 140, 24, 24, arrowButton[1]);

  // Enabled check box
  if (Lightsscreen == 1)
  {
    LightsEnabled = ledEn.En;
    myGLCD.print("Enabled", 38, 192);
    myFiles.load(41, 203, 30, 30, schedActiveB[LightsEnabled]);
  }
}

void screenCirc(byte Circscreen) // Circulation scheduling screen, screen draws based on circ Status
{

  dispScreen = 19;
  myGLCD.clrScr();

  char char3[3];
  char char3t[3];

  scheduleItem = Circscreen; // Track which status of circ we are editing

  // Draw header
  //  myFiles.load(2, 2, 30, 30, "1circ.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print("CIRCULATION", 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer
  myFiles.load(107, 294, 26, 26, "footschd.raw");

  // Circ On, Circ Off buttons to swap schedules
  myFiles.load(12, 71, 46, 22, "3on.raw");
  myFiles.load(12, 120, 46, 22, "3off.raw");


  myGLCD.drawLine(70, 70, 70, 170); // Separate line

  myGLCD.setColor(255, 255, 255);

  // Based on pump selected, get the schedule
  if (Circscreen == 1)
  {
    myGLCD.setColor(0, 255, 0);  // Green for Circ On
    myGLCD.print("Circ On", 85, 70);
    CircSchHour = circ.onHour;
    CircSchMin = circ.onMinute;
  }
  if (Circscreen == 2)
  {
    myGLCD.setColor(255, 0, 0);  // Red for Circ Off
    myGLCD.print("Circ Off", 85, 70);
    CircSchHour = circ.offHour;
    CircSchMin = circ.offMinute;
  }

  // Convert schedule to char and print
  itoa(CircSchHour, char3, 10);
  if (CircSchHour >= 0 && CircSchHour <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 120, 129);

  itoa(CircSchMin, char3, 10);
  if (CircSchMin >= 0 && CircSchMin <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 199, 129);

  // Buttons to set time
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("H", 93, 93);
  myFiles.load(85, 110, 24, 24, arrowButton[0]);
  myFiles.load(85, 140, 24, 24, arrowButton[1]);
  myGLCD.print("M", 172, 93);
  myFiles.load(164, 110, 24, 24, arrowButton[0]);
  myFiles.load(164, 140, 24, 24, arrowButton[1]);

  // Enabled check box
  if (Circscreen == 1)
  {
    CircEnabled = circEn.En;
    myGLCD.print("Enabled", 38, 192);
    myFiles.load(41, 203, 30, 30, schedActiveB[CircEnabled]);
  }
}


void screenClock()  // Time/date screen
{

  dispScreen = 6;

  myGLCD.clrScr();

  // Draw header
  myFiles.load(2, 2, 30, 30, "6clock.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(47, 168, 208);
  myGLCD.print("CLOCK     ", 36, 12);

  myGLCD.print("TIME", CENTER, 46);
  myGLCD.print("DATE", CENTER, 167);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header
  myGLCD.drawLine(0, 155, 239, 155); // Center line

  myGLCD.setFont(f_sinclair_S);
  myGLCD.setColor(255, 255, 255);

  // Draw clock buttons and text
  myGLCD.print("24H", 12, 72);
  myFiles.load(12, 89, 24, 24, arrowButton[0]);
  myFiles.load(12, 119, 24, 24, arrowButton[1]);
  myGLCD.print("M", 91, 72);
  myFiles.load(83, 89, 24, 24, arrowButton[0]);
  myFiles.load(83, 119, 24, 24, arrowButton[1]);
  myGLCD.print("S", 172, 72);
  myFiles.load(164, 89, 24, 24, arrowButton[0]);
  myFiles.load(164, 119, 24, 24, arrowButton[1]);

  // Draw date buttons and text
  myGLCD.print("M", 20, 194);
  myFiles.load(12, 211, 24, 24, arrowButton[0]);
  myFiles.load(12, 241, 24, 24, arrowButton[1]);
  myGLCD.print("D", 91, 194);
  myFiles.load(83, 211, 24, 24, arrowButton[0]);
  myFiles.load(83, 241, 24, 24, arrowButton[1]);
  myGLCD.print("Y", 172, 194);
  myFiles.load(164, 211, 24, 24, arrowButton[0]);
  myFiles.load(164, 241, 24, 24, arrowButton[1]);

  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(255, 77, 0);

  saveRTC.tHour = hour();
  saveRTC.tMinute = (minute() + 1); // Skip to the minute ahead to make it faster to set the time
  saveRTC.tSecond = 0; // Always have 0 seconds
  saveRTC.tDay = day();
  saveRTC.tMonth = month();
  saveRTC.tYear = (year() - 2000);

  char char3[3];
  char char3t[3];

  // Draw date and time to the screen
  itoa(saveRTC.tHour, char3, 10);
  if (saveRTC.tHour >= 0 && saveRTC.tHour <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 45, 108);

  itoa(saveRTC.tMinute, char3, 10);
  if (saveRTC.tMinute >= 0 && saveRTC.tMinute <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 123, 108);

  myGLCD.print("00", 201, 108);

  itoa(saveRTC.tMonth, char3, 10);
  if (saveRTC.tMonth >= 0 && saveRTC.tMonth <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 45, 230);

  itoa(saveRTC.tDay, char3, 10);
  if (saveRTC.tDay >= 0 && saveRTC.tDay <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 123, 230);

  itoa(saveRTC.tYear, char3, 10);
  if (saveRTC.tYear >= 0 && saveRTC.tYear <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 201, 230);

  // Buttons to save or cancel
  myFiles.load(12, 286, 84, 26, "6cancel.raw");
  myFiles.load(144, 286, 84, 26, "6set.raw");

}

void screenSTC() // STC screen
{

  dispScreen = 8;
  char char3[3]; // Used to convert numbers to char
  byte enabled;

  STC = EEPROM.read(18);

  myGLCD.clrScr();

  // Draw header
  myFiles.load(2, 2, 30, 30, "8heat.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(34, 81, 255);
  myGLCD.print("STC SETUP", 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer

  // Lines to divide screen
  myGLCD.drawLine(0, 131, 239, 131);
  myGLCD.drawLine(0, 212, 239, 212);

  myFiles.load(107, 294, 26, 26, "footextr.raw");

  // Draw the on icon
  myFiles.load(17, 150, 60, 51, "8on.raw");
  myGLCD.setColor(222, 8, 51);

  // Buttons for adjusting the on temp
  myFiles.load(162, 145, 24, 24, arrowButton[0]);
  myFiles.load(162, 175, 24, 24, arrowButton[1]);

  // Get the setting for fan on and print it
  byte STC = (EEPROM.read(18));
  itoa(STC, char3, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char3, 195, 164);

}

void screenSchedule() // Schedule screen
{
  dispScreen = 9;
  myGLCD.clrScr();

  // Draw header
  myFiles.load(2, 2, 30, 30, "9sched.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print("SCHEDULE", 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer
  myFiles.load(107, 294, 26, 26, "foothome.raw");

  // Draw schedule icons
  myFiles.load(10, 50, 48, 63, "4dosing.raw");
  myFiles.load(67, 50, 48, 63, "4co2.raw");
  myFiles.load(124, 50, 48, 63, "4lights.raw");
  myFiles.load(181, 50, 48, 63, "4circ.raw");
}

void screenDosing()  // Dosing pump screen
{

  dispScreen = 10;
  char char3[6]; // Used to convert numbers to char
  char char4[6];
  char char5[6];

  doseAmt1 = EEPROM.readFloat(201);
  doseAmt2 = EEPROM.readFloat(205);
  doseAmt3 = EEPROM.readFloat(209);

  myGLCD.clrScr();

  // Draw header
  myFiles.load(2, 2, 30, 30, "10dose.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(138, 93, 35);
  myGLCD.print("DOSING SETUP", 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header

  // 3 horizontal separate lines
  myGLCD.drawLine(0, 102, 239, 102);
  myGLCD.drawLine(0, 170, 239, 170);
  myGLCD.drawLine(0, 238, 239, 238);


  //Pump 1 dose
  myFiles.load(4, 113, 48, 48, "10dosing.raw");
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("Pump 1", 65, 130);
  myGLCD.print("ml", 65, 143);

  // Buttons to adjust pump 1 dose
  myFiles.load(145, 110, 24, 24, arrowButton[0]);
  myFiles.load(145, 140, 24, 24, arrowButton[1]);

  // Read dose amount setting and print it
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(f_arial_bold);
  dtostrf(doseAmt1, 4, 1, char3); //Convert to string
  myGLCD.print(char3, 170, 129);

  // Pump 2 dose
  myFiles.load(4, 181, 48, 48, "10dosing.raw");
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("Pump 2", 65, 198);
  myGLCD.print("ml", 65, 211);

  // Buttons to adjust pump 2 dose
  myFiles.load(145, 177, 24, 24, arrowButton[0]);
  myFiles.load(145, 207, 24, 24, arrowButton[1]);

  // Read dose amount setting and print it
  dtostrf(doseAmt2, 4, 1, char4);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(f_arial_bold);
  myGLCD.print(char4, 170, 197);

  // Pump 3 dose
  myFiles.load(4, 249, 48, 48, "10dosing.raw");
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("Pump 3", 65, 266);
  myGLCD.print("ml", 65, 279);

  // Buttons to adjust pump 3 dose
  myFiles.load(145, 244, 24, 24, arrowButton[0]);
  myFiles.load(145, 274, 24, 24, arrowButton[1]);

  // Read dose amount setting and print it
  dtostrf(doseAmt3, 4, 1, char5);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(f_arial_bold);
  myGLCD.print(char5, 170, 265);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw");

}

void screenResFill()  // Tank refill screen
{

  dispScreen = 11;
  char char3[4]; // Used to convent numbers to char
  char char4[4];
  char char5[4];

  doseCap1 = EEPROM.read(225);
  doseCap2 = EEPROM.read(226);
  doseCap3 = EEPROM.read(227);

  myGLCD.clrScr();

  // Draw header
  myFiles.load(2, 2, 30, 30, "11fill_s.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(138, 93, 35);
  myGLCD.print("TANK FILL", 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header

  // 3 horizontal separate lines
  myGLCD.drawLine(0, 102, 239, 102);
  myGLCD.drawLine(0, 170, 239, 170);
  myGLCD.drawLine(0, 238, 239, 238);

  //Tank 1 Cap
  myFiles.load(4, 113, 48, 48, "11fill.raw");
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("Tank 1", 65, 130);
  myGLCD.print("FULL", 65, 143);

  // Buttons to adjust tank 1 cap
  myFiles.load(145, 110, 24, 24, arrowButton[0]);
  myFiles.load(145, 140, 24, 24, arrowButton[1]);

  // Read tank cap setting and print it
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(f_arial_bold);
  itoa(doseCap1, char3, 10);
  byte px = 187;

  // Shift x coord to center text if needed
  if (doseCap1 > 999) px = 175;
  myGLCD.print(char3, px, 129);


  // Tank 2 Cap
  myFiles.load(4, 181, 48, 48, "11fill.raw");
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("Tank 2", 65, 198);
  myGLCD.print("FULL", 65, 211);

  // Buttons to adjust pump 2 dose
  myFiles.load(145, 177, 24, 24, arrowButton[0]);
  myFiles.load(145, 207, 24, 24, arrowButton[1]);

  // Read tank cap setting and print it
  itoa(doseCap2, char4, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(f_arial_bold);
  px = 187;

  // Shift x coord to center text if needed
  if (doseCap2 > 999) px = 175;
  myGLCD.print(char4, px, 197);


  // Tank 3 Cap
  myFiles.load(4, 249, 48, 48, "11fill.raw");
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("Tank 3", 65, 266);
  myGLCD.print("FULL", 65, 279);

  // Buttons to adjust pump 3 dose
  myFiles.load(145, 244, 24, 24, arrowButton[0]);
  myFiles.load(145, 274, 24, 24, arrowButton[1]);

  // Read tank cap setting and print it
  itoa(doseCap3, char5, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(f_arial_bold);
  px = 187;

  // shift x coord to center text if needed
  if (doseCap3 > 999) px = 175;
  myGLCD.print(char5, px, 265);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw");

}

void screenTestPump()  // Pump test screen
{

  dispScreen = 12;
  char char3[5]; // Used to convent numbers to char
  char char4[5];
  char char5[5];

  vol1 = EEPROM.readFloat(213);
  vol2 = EEPROM.readFloat(217);
  vol3 = EEPROM.readFloat(221);

  myGLCD.clrScr();

  // Draw header
  myFiles.load(2, 2, 30, 30, "12test_s.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(138, 93, 35);
  myGLCD.print("PUMP TEST", 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header

  // 3 horizontal separate lines
  myGLCD.drawLine(0, 102, 239, 102);
  myGLCD.drawLine(0, 170, 239, 170);
  myGLCD.drawLine(0, 238, 239, 238);

  // Pump 1 Test
  myFiles.load(4, 113, 48, 48, "12test.raw");
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("Pump 1", 65, 143);

  // Pump 2 Test
  myFiles.load(4, 181, 48, 48, "12test.raw");
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("Pump 2", 65, 211);

  // Pump 3 Test
  myFiles.load(4, 249, 48, 48, "12test.raw");
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("Pump 3", 65, 279);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw");

}

void screenDosingSched(byte pumpNo) // Pump scheduling screen, screen draws based on pump selected
{

  dispScreen = 15;
  myGLCD.clrScr();

  char char3[3];
  char char3t[3];

  scheduleItem = pumpNo; // Track which pump we are editing

  // Draw header
  myFiles.load(2, 2, 30, 30, "9sched.raw");
  myGLCD.setFont(f_arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print("SCHEDULE", 36, 12);

  myGLCD.setColor(138, 93, 35);
  myGLCD.print("DOSING", 36, 34);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // Under header
  myGLCD.drawLine(0, 307, 104, 307); // Left footer
  myGLCD.drawLine(136, 307, 239, 307); // Right footer
  myFiles.load(107, 294, 26, 26, "footschd.raw");

  // Pump1, pump2 and pump3 buttons to swap schedules
  myFiles.load(12, 71, 30, 30, "15pump1.raw");
  myFiles.load(12, 120, 30, 30, "15pump2.raw");
  myFiles.load(12, 169, 30, 30, "15pump3.raw");

  myGLCD.drawLine(70, 70, 70, 170); // Separate line

  myGLCD.setColor(255, 255, 255);

  // Based on pump selected, get the schedule
  if (pumpNo == 1)
  {
    myGLCD.setColor(255, 0, 0);  // Red for pump1
    myGLCD.print("Pump 1", 85, 70);
    DoseSchHour = pump1.onHour;
    DoseSchMin = pump1.onMinute;
    daySun = pump1.Sun;
    dayMon = pump1.Mon;
    dayTue = pump1.Tue;
    dayWed = pump1.Wed;
    dayThu = pump1.Thu;
    dayFri = pump1.Fri;
    daySat = pump1.Sat;
  }
  if (pumpNo == 2)
  {
    myGLCD.setColor(0, 255, 0);  // Green for pump2
    myGLCD.print("Pump 2", 85, 70);
    DoseSchHour = pump2.onHour;
    DoseSchMin = pump2.onMinute;
    daySun = pump2.Sun;
    dayMon = pump2.Mon;
    dayTue = pump2.Tue;
    dayWed = pump2.Wed;
    dayThu = pump2.Thu;
    dayFri = pump2.Fri;
    daySat = pump2.Sat;
  }
  if (pumpNo == 3)
  {
    myGLCD.setColor(0, 0, 255);  // Blue for pump3
    myGLCD.print("Pump 3", 85, 70);
    DoseSchHour = pump3.onHour;
    DoseSchMin = pump3.onMinute;
    daySun = pump3.Sun;
    dayMon = pump3.Mon;
    dayTue = pump3.Tue;
    dayWed = pump3.Wed;
    dayThu = pump3.Thu;
    dayFri = pump3.Fri;
    daySat = pump3.Sat;
  }

  // Convert schedule to char and print
  itoa(DoseSchHour, char3, 10);
  if (DoseSchHour >= 0 && DoseSchHour <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 120, 129);

  itoa(DoseSchMin, char3, 10);
  if (DoseSchMin >= 0 && DoseSchMin <= 9) // Add a zero
  {
    itoa(0, char3t, 10); // Make char3t 0
    strcat(char3t, char3);
    strcpy (char3, char3t);
  }
  myGLCD.print(char3, 199, 129);

  // Buttons to set time
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(f_sinclair_S);
  myGLCD.print("H", 93, 93);
  myFiles.load(85, 110, 24, 24, arrowButton[0]);
  myFiles.load(85, 140, 24, 24, arrowButton[1]);
  myGLCD.print("M", 172, 93);
  myFiles.load(164, 110, 24, 24, arrowButton[0]);
  myFiles.load(164, 140, 24, 24, arrowButton[1]);

  // Days of the week check boxes
  myGLCD.print("SUN", 54, 192);
  myFiles.load(51, 203, 30, 30, schedActiveB[daySun]);
  myGLCD.print("MON", 108, 192);
  myFiles.load(105, 203, 30, 30, schedActiveB[dayMon]);
  myGLCD.print("TUE", 162, 192);
  myFiles.load(159, 203, 30, 30, schedActiveB[dayTue]);
  myGLCD.print("WED", 33, 239);
  myFiles.load(30, 250, 30, 30, schedActiveB[dayWed]);
  myGLCD.print("THU", 87, 239);
  myFiles.load(84, 250, 30, 30, schedActiveB[dayThu]);
  myGLCD.print("FRI", 135, 239);
  myFiles.load(132, 250, 30, 30, schedActiveB[dayFri]);
  myGLCD.print("SAT", 189, 239);
  myFiles.load(186, 250, 30, 30, schedActiveB[daySat]);

}














