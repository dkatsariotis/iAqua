void processMyTouch() // This is a huge block dedicated to processing all touch screen events
{
  myTouch.read();
  x = myTouch.getX();
  y = myTouch.getY();

  // Initiate char vars for converting numbers to char for display
  char char3[3];
  char char3t[3];
  char char4[4];
  char char5[5];

  // We evaluate touch based on which screen we are in

  switch (dispScreen)

  {

    case 1: // Home screen

      if ((x >= 10) && (x <= 58) && (y >= 266) && (y <= 314))
      {
        screenHome();
      }
      if ((x >= 67) && (x <= 115) && (y >= 266) && (y <= 314))
      {
        screenSchedule();
      }
      if ((x >= 124) && (x <= 172) && (y >= 266) && (y <= 314))
      {
        screenPower();
      }

      if ((x >= 181) && (x <= 229) && (y >= 266) && (y <= 314))
      {
        screenSettings();
      }
      break;


    case 3: // Power control screen

      if ((x >= 69) && (x <= 118) && (y >= 77) && (y <= 125)) // All on
      {
        // Turn on all power outputs
        AlarmPwrLights_On();
        AlarmPwrFan_On();
        AlarmPwrHeater_On();
        AlarmPwrCO2_On();
        AlarmPwrCirc_On();
        screenPower(); // Redraw screen

      }
      else if ((x >= 125) && (x <= 174) && (y >= 77) && (y <= 125)) // All off
      {
        // Turn off all power outputs
        AlarmPwrLights_Off();
        AlarmPwrFan_Off();
        AlarmPwrHeater_Off();
        AlarmPwrCO2_Off();
        AlarmPwrCirc_Off();
        screenPower(); // Redraw screen
      }

      else if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318))
      {
        screenHome();
      }

      else if ((x >= 15) && (x <= 64) && (y >= 139) && (y <= 187)) // Lights power
      {
        //toggle power
        if (!globalPower.pwrLights)
        {
          AlarmPwrLights_On();
        }
        else if (globalPower.pwrLights)
        {
          AlarmPwrLights_Off();
        }
        // draw icons
        myFiles.load(15, 139, 48, 48, pwrLightIcon[globalPower.pwrLights]);
        myFiles.load(34, 192, 10, 11, pwrDot[globalPower.pwrLights]);
      }

      else if ((x >= 69) && (x <= 118) && (y >= 139) && (y <= 187)) // Circ power
      {
        //toggle power
        if (!globalPower.pwrCirc)
        {
          AlarmPwrCirc_On();
        }
        else if (globalPower.pwrCirc)
        {
          AlarmPwrCirc_Off();
        }
        // draw icons
        myFiles.load(69, 139, 48, 48, pwrCircIcon[globalPower.pwrCirc]);
        myFiles.load(88, 192, 10, 11, pwrDot[globalPower.pwrCirc]);
      }

      else if ((x >= 123) && (x <= 171) && (y >= 139) && (y <= 187)) // Heater power
      {
        //toggle power
        if (!globalPower.pwrHeater)
        {
          AlarmPwrHeater_On();
        }
        else if (globalPower.pwrHeater)
        {
          AlarmPwrHeater_Off();
        }
        // draw icons
        myFiles.load(123, 139, 48, 48, pwrHeatIcon[globalPower.pwrHeater]);
        myFiles.load(142, 192, 10, 11, pwrDot[globalPower.pwrHeater]);
      }

      else if ((x >= 15) && (x <= 64) && (y >= 198) && (y <= 246)) // Fan power
      {
        // Toggle power
        if (!globalPower.pwrFan)
        {
          AlarmPwrFan_On();
        }
        else if (globalPower.pwrFan)
        {
          AlarmPwrFan_Off();
        }
        // Draw icons
        myFiles.load(15, 212, 48, 48, pwrFanIcon[globalPower.pwrFan] );
        myFiles.load(34, 264, 10, 11, pwrDot[globalPower.pwrFan]);
      }

      else if ((x >= 69) && (x <= 118) && (y >= 198) && (y <= 246)) // CO2 power
      {
        // toggle power
        if (!globalPower.pwrCO2)
        {
          AlarmPwrCO2_On();
        }
        else if (globalPower.pwrCO2) {
          AlarmPwrCO2_Off();
        }
        // draw icons
        myFiles.load(69, 212, 48, 48, pwrCO2Icon[globalPower.pwrCO2] );
        myFiles.load(88, 264, 10, 11, pwrDot[globalPower.pwrCO2]);
      }

      else if ((x >= 181) && (x <= 229) && (y >= 198) && (y <= 246)) // Reset Arduino
      {
        software_Reset();
      }

      break;

    case 4: // Settings screen

      if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318))
      {
        screenHome();
      }

      else if ((x >= 10) && (x <= 58) && (y >= 50) && (y <= 113))
      {
        screenClock();
      }
      else if ((x >= 67) && (x <= 115) && (y >= 50) && (y <= 113))
      {
        screenScreen();
      }
      else if ((x >= 124) && (x <= 172) && (y >= 50) && (y <= 113))
      {
        screenSTC();
      }
      else if ((x >= 181) && (x <= 229) && (y >= 50) && (y <= 113))
      {
        screenDosing();
      }
      else if ((x >= 10) && (x <= 58) && (y >= 118) && (y <= 181))
      {
        screenTestPump();
      }
      else if ((x >= 67) && (x <= 115) && (y >= 118) && (y <= 181))
      {
        screenResFill();
      }

      break;


    case 6: // Clock screen

      itoa(0, char3t, 10); // Make char3t 0

      myGLCD.setFont(f_arial_bold);
      myGLCD.setColor(255, 77, 0);

      if ((x >= 12) && (x <= 96) && (y >= 286) && (y <= 312)) // Cancel button
      {
        screenSettings();
      }
      else if ((x >= 144) && (x <= 228) && (y >= 286) && (y <= 312)) // Save button
      {
        SaveTime();
        screenSettings();
      }
      else if ((x >= 12) && (x <= 36) && (y >= 89) && (y <= 113)) // Hour up button
      {
        saveRTC.tHour = (saveRTC.tHour + 1);
        if (saveRTC.tHour > 23) saveRTC.tHour = 0;
        itoa(saveRTC.tHour, char3, 10);
        if (saveRTC.tHour >= 0 && saveRTC.tHour <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 45, 108);
      }
      else if ((x >= 12) && (x <= 36) && (y >= 119) && (y <= 143)) // Hour down button
      {
        saveRTC.tHour = (saveRTC.tHour - 1);
        if (saveRTC.tHour < 0) saveRTC.tHour = 23;
        itoa(saveRTC.tHour, char3, 10);
        if (saveRTC.tHour >= 0 && saveRTC.tHour <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 45, 108);
      }
      else if ((x >= 83) && (x <= 107) && (y >= 89) && (y <= 113)) // Min up button
      {
        saveRTC.tMinute = (saveRTC.tMinute + 1);
        if (saveRTC.tMinute > 59) saveRTC.tMinute = 0;
        itoa(saveRTC.tMinute, char3, 10);
        if (saveRTC.tMinute >= 0 && saveRTC.tMinute <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 123, 108);

      }
      else if ((x >= 83) && (x <= 107) && (y >= 119) && (y <= 143)) // Min down button
      {
        saveRTC.tMinute = (saveRTC.tMinute - 1);
        if (saveRTC.tMinute < 0) saveRTC.tMinute = 59;
        itoa(saveRTC.tMinute, char3, 10);
        if (saveRTC.tMinute >= 0 && saveRTC.tMinute <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 123, 108);
      }
      else if ((x >= 164) && (x <= 188) && (y >= 89) && (y <= 113)) // Sec up button
      {
        saveRTC.tSecond = (saveRTC.tSecond + 1);
        if (saveRTC.tSecond > 59) saveRTC.tSecond = 0;
        itoa(saveRTC.tSecond, char3, 10);
        if (saveRTC.tSecond >= 0 && saveRTC.tSecond <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 201, 108);

      }
      else if ((x >= 164) && (x <= 188) && (y >= 119) && (y <= 143)) // Sec down button
      {
        saveRTC.tSecond = (saveRTC.tSecond - 1);
        if (saveRTC.tSecond < 0) saveRTC.tSecond = 59;
        itoa(saveRTC.tSecond, char3, 10);
        if (saveRTC.tSecond >= 0 && saveRTC.tSecond <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 201, 108);
      }

      else if ((x >= 12) && (x <= 36) && (y >= 211) && (y <= 235)) // Month up button
      {
        saveRTC.tMonth = (saveRTC.tMonth + 1);
        if (saveRTC.tMonth > 12) saveRTC.tMonth = 1;
        itoa(saveRTC.tMonth, char3, 10);
        if (saveRTC.tMonth >= 0 && saveRTC.tMonth <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 45, 230);

      }
      else if ((x >= 12) && (x <= 36) && (y >= 241) && (y <= 265)) // Month down button
      {
        saveRTC.tMonth = (saveRTC.tMonth - 1);
        if (saveRTC.tMonth < 1) saveRTC.tMonth = 12;
        itoa(saveRTC.tMonth, char3, 10);
        if (saveRTC.tMonth >= 0 && saveRTC.tMonth <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 45, 230);
      }
      else if ((x >= 83) && (x <= 107) && (y >= 211) && (y <= 235)) // Day up button
      {
        saveRTC.tDay = (saveRTC.tDay + 1);
        if (saveRTC.tDay > 31) saveRTC.tDay = 1;
        itoa(saveRTC.tDay, char3, 10);
        if (saveRTC.tDay >= 0 && saveRTC.tDay <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 123, 230);

      }
      else if ((x >= 83) && (x <= 107) && (y >= 241) && (y <= 265)) // Day down button
      {
        saveRTC.tDay = (saveRTC.tDay - 1);
        if (saveRTC.tDay < 1) saveRTC.tDay = 31;
        itoa(saveRTC.tDay, char3, 10);
        if (saveRTC.tDay >= 0 && saveRTC.tDay <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 123, 230);
      }
      else if ((x >= 164) && (x <= 188) && (y >= 211) && (y <= 235)) // Year up button
      {
        saveRTC.tYear = (saveRTC.tYear + 1);
        if (saveRTC.tYear > 99) saveRTC.tYear = 0;
        itoa(saveRTC.tYear, char3, 10);
        if (saveRTC.tYear >= 0 && saveRTC.tYear <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 201, 230);

      }
      else if ((x >= 164) && (x <= 188) && (y >= 241) && (y <= 265)) // Year down button
      {
        saveRTC.tYear = (saveRTC.tYear - 1);
        if (saveRTC.tYear < 0) saveRTC.tYear = 99;
        itoa(saveRTC.tYear, char3, 10);
        if (saveRTC.tYear >= 0 && saveRTC.tYear <= 9) // Add a zero
        {
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 201, 230);
      }

      break;

    case 8: // STC settings screen

      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(f_arial_bold);

      if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318)) // Settings button
      {
        EEPROM.update(18, STC);
        STCTemp = EEPROM.read(18);
        screenSettings();
      }
      else if ((x >= 162) && (x <= 186) && (y >= 145) && (y <= 169)) // Fan on up button
      {
        STC = STC + 1;
        itoa(STC, char3, 10);
        myGLCD.print(char3, 195, 164);

      }
      else if ((x >= 162) && (x <= 186) && (y >= 175) && (y <= 199)) // Fan on down button
      {
        STC = STC - 1;
        itoa(STC, char3, 10);
        myGLCD.print(char3, 195, 164);

      }

      break;

    case 9: // Schedule screen

      if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318)) // Home button
      {
        readPowerSchedule(); // Load power schedule from eeprom
        readDosingSchedule(); // Load dosing schedule from eeprom
        updateAlarms(); // This will rebuild all of the schedules
        smartStartup(); // Apply Alarms
        screenHome();
      }

      else if ((x >= 10) && (x <= 58) && (y >= 50) && (y <= 113))
      {
        screenDosingSched(1); // Send 1 to start with pump 1
      }
      else if ((x >= 67) && (x <= 115) && (y >= 50) && (y <= 113))
      {
        screenCO2(1);
      }
      else if ((x >= 124) && (x <= 172) && (y >= 50) && (y <= 113))
      {
        screenLights(1);
      }
      else if ((x >= 181) && (x <= 219) && (y >= 50) && (y <= 113))
      {
        screenCirc(1);
      }

      break;

    case 10: // Dosing screen

      if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318)) // Settings button
      {
        EEPROM.updateFloat(201, doseAmt1);
        EEPROM.updateFloat(205, doseAmt2);
        EEPROM.updateFloat(209, doseAmt3);
        screenSettings();
      }

      else if ((x >= 145) && (x <= 169) && (y >= 110) && (y <= 134)) // Pump1 dose increase
      {
        if (doseAmt1 <= 9.9) //Max 10ml
          doseAmt1 = (doseAmt1 + .1);
        dtostrf(doseAmt1, 4, 1, char3);
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(175, 130, 239, 146); // Clear previous value
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char3, 170, 129);
      }
      else if ((x >= 145) && (x <= 169) && (y >= 140) && (y <= 164)) // Pump 1 dose decrease
      {
        if (doseAmt1 > 0) //Min 0ml
          doseAmt1 = (doseAmt1 - .1);
        dtostrf(doseAmt1, 4, 1, char3);
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(175, 130, 239, 146); // Clear previous value
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char3, 170, 129);
      }
      else if ((x >= 145) && (x <= 169) && (y >= 177) && (y <= 201)) // Pump 2 dose increase
      {
        if (doseAmt2 <= 9.9) //Max 10ml
          doseAmt2 = (doseAmt2 + .1);
        dtostrf(doseAmt2, 4, 1, char4);
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(175, 197, 239, 213); // Clear previous value
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char4, 170, 197);

      }
      else if ((x >= 145) && (x <= 169) && (y >= 207) && (y <= 231)) // Pump 2 dose decrease
      {
        if (doseAmt2 > 0) //Min 0ml
          doseAmt2 = (doseAmt2 - .1);
        dtostrf(doseAmt2, 4, 1, char4);
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(175, 197, 239, 213); // Clear previous value
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char4, 170, 197);
      }
      else if ((x >= 145) && (x <= 169) && (y >= 244) && (y <= 268)) // Pump 3 dose increase
      {
        if (doseAmt3 <= 9.9) //Max 10ml
          doseAmt3 = (doseAmt3 + .1);
        dtostrf(doseAmt3, 4, 1, char5);
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(175, 264, 239, 280); // Clear previous value
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char5, 170, 265);

      }
      else if ((x >= 145) && (x <= 169) && (y >= 274) && (y <= 298)) // Pump 3 dose decrease
      {
        if (doseAmt3 > 0) //Min 0ml
          doseAmt3 = (doseAmt3 - .1);
        dtostrf(doseAmt3, 4, 1, char5);
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(175, 264, 239, 280); // Clear previous value
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char5, 170, 265);
      }

      break;

    case 11: // Tank refill screen

      if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318)) // Settings button
      {
        EEPROM.update(225, doseCap1);
        EEPROM.update(226, doseCap2);
        EEPROM.update(227, doseCap3);
        screenSettings();
      }
      else if ((x >= 145) && (x <= 169) && (y >= 110) && (y <= 134)) // Tank 1 Cap increase
      {
        if (doseCap1 <= 250) //Max 250ml
          doseCap1 = (doseCap1 + 5);
        itoa(doseCap1, char3, 10);
        byte px = 187;
        if (doseCap1 > 999) px = 175;
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char3, px, 129);
      }
      else if ((x >= 145) && (x <= 169) && (y >= 140) && (y <= 164)) // Tank 1 Cap decrease
      {
        if (doseCap1 > 0) //Min 0ml
          doseCap1 = (doseCap1 - 5);
        itoa(doseCap1, char3, 10);
        byte px = 187;
        if (doseCap1 > 999) px = 175;
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(175, 130, 239, 146); // Clear previous value
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char3, px, 129);
      }
      else if ((x >= 145) && (x <= 169) && (y >= 177) && (y <= 201)) // Tank 2 Cap increase
      {
        if (doseCap2 <= 250) //Max 250ml
          doseCap2 = (doseCap2 + 5);
        itoa(doseCap2, char4, 10);
        byte px = 187;
        if (doseCap2 > 999) px = 175;
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char4, px, 197);

      }
      else if ((x >= 145) && (x <= 169) && (y >= 207) && (y <= 231)) // Tank 2 Cap decrease
      {
        if (doseCap2 > 0) //Min 0ml
          doseCap2 = (doseCap2 - 5);
        itoa(doseCap2, char4, 10);
        byte px = 187;
        if (doseCap2 > 999) px = 175;
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(175, 197, 239, 213); // Clear previous value
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char4, px, 197);
      }
      else if ((x >= 145) && (x <= 169) && (y >= 244) && (y <= 268)) // Tank 3 Cap increase
      {
        if (doseCap3 <= 250) //Max 250ml
          doseCap3 = (doseCap3 + 5);
        itoa(doseCap3, char5, 10);
        byte px = 187;
        if (doseCap3 > 999) px = 175;
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char5, px, 265);

      }
      else if ((x >= 145) && (x <= 169) && (y >= 274) && (y <= 298)) // Tank 3 Cap decrease
      {
        if (doseCap3 > 0) //Min 0ml
          doseCap3 = (doseCap3 - 5);
        itoa(doseCap3, char5, 10);
        byte px = 187;
        if (doseCap3 > 999) px = 175;
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(175, 264, 239, 280); // Clear previous value
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_arial_bold);
        myGLCD.print(char5, px, 265);
      }
      else if ((x >= 4) && (x <= 52) && (y >= 113) && (y <= 161)) // Tank 1 refill button
      {
        EEPROM.updateFloat(213, doseCap1);
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_sinclair_S);
        myGLCD.print("FULL", 65, 143);
      }
      else if ((x >= 4) && (x <= 52) && (y >= 181) && (y <= 229)) // Tank 2 refill button
      {
        EEPROM.updateFloat(217, doseCap2);
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_sinclair_S);
        myGLCD.print("FULL", 65, 211);
      }
      else if ((x >= 4) && (x <= 52) && (y >= 249) && (y <= 297)) // Tank 3 refill button
      {
        EEPROM.updateFloat(221, doseCap3);
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(f_sinclair_S);
        myGLCD.print("FULL", 65, 279);
      }

      break;

    case 12: // Pump test screen


      if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318)) // Settings button
      {
        EEPROM.updateFloat(213, vol1);
        EEPROM.updateFloat(217, vol2);
        EEPROM.updateFloat(221, vol3);
        web = 9;
        websection();
        screenSettings();
      }
      else if ((x >= 4) && (x <= 52) && (y >= 113) && (y <= 161)) // Pump1 test button
      {
        analogWrite(pump1Pump, 0);
        delay(1000);
        analogWrite(pump1Pump, 255);

        // Update tank volume
        vol1 = (vol1 - 1);

      }
      else if ((x >= 4) && (x <= 52) && (y >= 181) && (y <= 229)) // Pump2 test button
      {
        analogWrite(pump2Pump, 0);
        delay(1000);
        analogWrite(pump2Pump, 255);

        // Update tank volume
        vol2 = (vol2 - 1);

      }
      else if ((x >= 4) && (x <= 52) && (y >= 249) && (y <= 297)) // Pump3 test button
      {
        analogWrite(pump3Pump, 0);
        delay(1000);
        analogWrite(pump3Pump, 255);

        // Update tank volume
        vol3 = (vol3 - 1);

      }

      break;

    case 15: // Pump1, pump2 and pump3 dosing schedule

      // ScheduleItem 1 = pump1
      // ScheduleItem 2 = pump2
      // ScheduleItem 3 = pump3
      myGLCD.setFont(f_arial_bold);

      // Set font color based on pump1, pump2 or pump3
      if (scheduleItem == 1) myGLCD.setColor(255, 0, 0);
      if (scheduleItem == 2) myGLCD.setColor(0, 255, 0);
      if (scheduleItem == 3) myGLCD.setColor(0, 0, 255);

      if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318)) // Schedule button
      {
        screenSchedule();
      }

      else if ((x >= 12) && (x <= 42) && (y >= 71) && (y <= 101)) // Pump1 button
      {
        if (scheduleItem != 1) screenDosingSched(1); // Switch to pump1 schedule
      }
      else if ((x >= 12) && (x <= 42) && (y >= 120) && (y <= 150)) // Pump2 button
      {
        if (scheduleItem != 2) screenDosingSched(2); // Switch to pump2 schedule
      }
      else if ((x >= 12) && (x <= 42) && (y >= 169) && (y <= 199)) // Pump3 button
      {
        if (scheduleItem != 3) screenDosingSched(3); // Switch to pump3 schedule
      }
      else if ((x >= 85) && (x <= 109) && (y >= 110) && (y <= 134)) // On hour up
      {

        if (scheduleItem == 1)
        {
          if (pump1.onHour == 23) pump1.onHour = 0;
          else pump1.onHour = pump1.onHour + 1;
          DoseHour = pump1.onHour;
          EEPROM.update(300, DoseHour);
        }
        else if (scheduleItem == 2)
        {
          if (pump2.onHour == 23) pump2.onHour = 0;
          else pump2.onHour = pump2.onHour + 1;
          DoseHour = pump2.onHour;
          EEPROM.update(309, DoseHour);
        }
        else if (scheduleItem == 3)
        {
          if (pump3.onHour == 23) pump3.onHour = 0;
          else pump3.onHour = pump3.onHour + 1;
          DoseHour = pump3.onHour;
          EEPROM.update(318, DoseHour);
        }
        // Print to screen
        itoa(DoseHour, char3, 10);
        if (DoseHour >= 0 && DoseHour <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 120, 129);

      }
      else if ((x >= 85) && (x <= 109) && (y >= 140) && (y <= 164)) // On hour down
      {

        if (scheduleItem == 1)
        {
          if (pump1.onHour == 0) pump1.onHour = 23;
          else pump1.onHour = pump1.onHour - 1;
          DoseHour = pump1.onHour;
          EEPROM.update(300, DoseHour);
        }
        else if (scheduleItem == 2)
        {
          if (pump2.onHour == 0) pump2.onHour = 23;
          else pump2.onHour = pump2.onHour - 1;
          DoseHour = pump2.onHour;
          EEPROM.update(309, DoseHour);
        }
        else if (scheduleItem == 3)
        {
          if (pump3.onHour == 0) pump3.onHour = 23;
          else pump3.onHour = pump3.onHour - 1;
          DoseHour = pump3.onHour;
          EEPROM.update(318, DoseHour);
        }
        // Print to screen
        itoa(DoseHour, char3, 10);
        if (DoseHour >= 0 && DoseHour <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 120, 129);
      }

      else if ((x >= 164) && (x <= 188) && (y >= 110) && (y <= 134)) // On min up
      {

        if (scheduleItem == 1)
        {
          if (pump1.onMinute == 59) pump1.onMinute = 0;
          else pump1.onMinute = pump1.onMinute + 1;
          DoseMinute = pump1.onMinute;
          EEPROM.update(301, DoseMinute);
        }
        else if (scheduleItem == 2)
        {
          if (pump2.onMinute == 59) pump2.onMinute = 0;
          else pump2.onMinute = pump2.onMinute + 1;
          DoseMinute = pump2.onMinute;
          EEPROM.update(310, DoseMinute);
        }
        else if (scheduleItem == 3)
        {
          if (pump3.onMinute == 59) pump3.onMinute = 0;
          else pump3.onMinute = pump3.onMinute + 1;
          DoseMinute = pump3.onMinute;
          EEPROM.update(319, DoseMinute);
        }
        // Print to screen
        itoa(DoseMinute, char3, 10);
        if (DoseMinute >= 0 && DoseMinute <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 199, 129);
      }
      else if ((x >= 164) && (x <= 188) && (y >= 140) && (y <= 164)) // On min down
      {

        if (scheduleItem == 1)
        {
          if (pump1.onMinute == 0) pump1.onMinute = 59;
          else pump1.onMinute = pump1.onMinute - 1;
          DoseMinute = pump1.onMinute;
          EEPROM.update(301, DoseMinute);
        }
        else if (scheduleItem == 2)
        {
          if (pump2.onMinute == 0) pump2.onMinute = 59;
          else pump2.onMinute = pump2.onMinute - 1;
          DoseMinute = pump2.onMinute;
          EEPROM.update(310, DoseMinute);
        }
        else if (scheduleItem == 3)
        {
          if (pump3.onMinute == 0) pump3.onMinute = 59;
          else pump3.onMinute = pump3.onMinute - 1;
          DoseMinute = pump3.onMinute;
          EEPROM.update(319, DoseMinute);
        }
        // Print to screen
        itoa(DoseMinute, char3, 10);
        if (DoseMinute >= 0 && DoseMinute <= 9) // add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 199, 129);
      }
      else if ((x >= 51) && (x <= 81) && (y >= 203) && (y <= 233)) // Dose on Sun
      {
        if (scheduleItem == 1)
        {
          if (pump1.Sun == 1) pump1.Sun = 0;
          else pump1.Sun = 1;
          EEPROM.update(302, pump1.Sun);
          myFiles.load(51, 203, 30, 30, schedActiveB[pump1.Sun]);
        }
        if (scheduleItem == 2)
        {
          if (pump2.Sun == 1) pump2.Sun = 0;
          else pump2.Sun = 1;
          EEPROM.update(311, pump2.Sun);
          myFiles.load(51, 203, 30, 30, schedActiveB[pump2.Sun]);
        }
        if (scheduleItem == 3)
        {
          if (pump3.Sun == 1) pump3.Sun = 0;
          else pump3.Sun = 1;
          EEPROM.update(320, pump3.Sun);
          myFiles.load(51, 203, 30, 30, schedActiveB[pump3.Sun]);
        }
      }
      else if ((x >= 105) && (x <= 135) && (y >= 203) && (y <= 233)) // Dose on Mon
      {
        if (scheduleItem == 1)
        {
          if (pump1.Mon == 1) pump1.Mon = 0;
          else pump1.Mon = 1;
          EEPROM.update(303, pump1.Mon);
          myFiles.load(105, 203, 30, 30, schedActiveB[pump1.Mon]);
        }
        if (scheduleItem == 2)
        {
          if (pump2.Mon == 1) pump2.Mon = 0;
          else pump2.Mon = 1;
          EEPROM.update(312, pump2.Mon);
          myFiles.load(105, 203, 30, 30, schedActiveB[pump2.Mon]);
        }
        if (scheduleItem == 3)
        {
          if (pump3.Mon == 1) pump3.Mon = 0;
          else pump3.Mon = 1;
          EEPROM.update(321, pump3.Mon);
          myFiles.load(105, 203, 30, 30, schedActiveB[pump3.Mon]);
        }
      }
      else if ((x >= 159) && (x <= 189) && (y >= 203) && (y <= 233)) // Dose on Tue
      {
        if (scheduleItem == 1)
        {
          if (pump1.Tue == 1) pump1.Tue = 0;
          else pump1.Tue = 1;
          EEPROM.update(304, pump1.Tue);
          myFiles.load(159, 203, 30, 30, schedActiveB[pump1.Tue]);
        }
        if (scheduleItem == 2)
        {
          if (pump2.Tue == 1) pump2.Tue = 0;
          else pump2.Tue = 1;
          EEPROM.update(313, pump2.Tue);
          myFiles.load(159, 203, 30, 30, schedActiveB[pump2.Tue]);
        }
        if (scheduleItem == 3)
        {
          if (pump3.Tue == 1) pump3.Tue = 0;
          else pump3.Tue = 1;
          EEPROM.update(322, pump3.Tue);
          myFiles.load(159, 203, 30, 30, schedActiveB[pump3.Tue]);
        }
      }
      else if ((x >= 30) && (x <= 60) && (y >= 250) && (y <= 280)) // Dose on Wed
      {
        if (scheduleItem == 1)
        {
          if (pump1.Wed == 1) pump1.Wed = 0;
          else pump1.Wed = 1;
          EEPROM.update(305, pump1.Wed);
          myFiles.load(30, 250, 30, 30, schedActiveB[pump1.Wed]);
        }
        if (scheduleItem == 2)
        {
          if (pump2.Wed == 1) pump2.Wed = 0;
          else pump2.Wed = 1;
          EEPROM.update(314, pump2.Wed);
          myFiles.load(30, 250, 30, 30, schedActiveB[pump2.Wed]);
        }
        if (scheduleItem == 3)
        {
          if (pump3.Wed == 1) pump3.Wed = 0;
          else pump3.Wed = 1;
          EEPROM.update(323, pump3.Wed);
          myFiles.load(30, 250, 30, 30, schedActiveB[pump3.Wed]);
        }
      }
      else if ((x >= 84) && (x <= 114) && (y >= 250) && (y <= 280)) // Dose on Thu
      {
        if (scheduleItem == 1)
        {
          if (pump1.Thu == 1) pump1.Thu = 0;
          else pump1.Thu = 1;
          EEPROM.update(306, pump1.Thu);
          myFiles.load(84, 250, 30, 30, schedActiveB[pump1.Thu]);
        }
        if (scheduleItem == 2)
        {
          if (pump2.Thu == 1) pump2.Thu = 0;
          else pump2.Thu = 1;
          EEPROM.update(315, pump2.Thu);
          myFiles.load(84, 250, 30, 30, schedActiveB[pump2.Thu]);
        }
        if (scheduleItem == 3)
        {
          if (pump3.Thu == 1) pump3.Thu = 0;
          else pump3.Thu = 1;
          EEPROM.update(324, pump3.Thu);
          myFiles.load(84, 250, 30, 30, schedActiveB[pump3.Thu]);
        }
      }
      else if ((x >= 132) && (x <= 162) && (y >= 250) && (y <= 280)) // Dose on Fri
      {
        if (scheduleItem == 1)
        {
          if (pump1.Fri == 1) pump1.Fri = 0;
          else pump1.Fri = 1;
          EEPROM.update(307, pump1.Fri);
          myFiles.load(132, 250, 30, 30, schedActiveB[pump1.Fri]);
        }
        if (scheduleItem == 2)
        {
          if (pump2.Fri == 1) pump2.Fri = 0;
          else pump2.Fri = 1;
          EEPROM.update(316, pump2.Fri);
          myFiles.load(132, 250, 30, 30, schedActiveB[pump2.Fri]);
        }
        if (scheduleItem == 3)
        {
          if (pump3.Fri == 1) pump3.Fri = 0;
          else pump3.Fri = 1;
          EEPROM.update(325, pump3.Fri);
          myFiles.load(132, 250, 30, 30, schedActiveB[pump3.Fri]);
        }
      }
      else if ((x >= 186) && (x <= 216) && (y >= 250) && (y <= 280)) // Dose on Sat
      {
        if (scheduleItem == 1)
        {
          if (pump1.Sat == 1) pump1.Sat = 0;
          else pump1.Sat = 1;
          EEPROM.update(308, pump1.Sat);
          myFiles.load(186, 250, 30, 30, schedActiveB[pump1.Sat]);
        }
        if (scheduleItem == 2)
        {
          if (pump2.Sat == 1) pump2.Sat = 0;
          else pump2.Sat = 1;
          EEPROM.update(317, pump2.Sat);
          myFiles.load(186, 250, 30, 30, schedActiveB[pump2.Sat]);
        }
        if (scheduleItem == 3)
        {
          if (pump3.Sat == 1) pump3.Sat = 0;
          else pump3.Sat = 1;
          EEPROM.update(326, pump3.Sat);
          myFiles.load(186, 250, 30, 30, schedActiveB[pump3.Sat]);
        }
      }
      break;

    case 16:  // Screen settings

      myGLCD.setFont(f_arial_bold);

      if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318)) // Settings button
      {
        screenSettings();
      }

      else if ((x >= 145) && (x <= 169) && (y >= 42) && (y <= 66)) // Return home min up
      {
        if (screenRetHome < 255)
        {
          screenRetHome = screenRetHome + 1;
          itoa(screenRetHome, char3, 10);
          if (screenRetHome >= 0 && screenRetHome <= 9) // Add a zero
          {
            myGLCD.setColor(0, 0, 0);
            myGLCD.fillRect(191, 59, 239, 75); // Clear previous value
          }
          myGLCD.setColor(255, 77, 0);
          myGLCD.print(char3, 191, 59);
          EEPROM.update(28, screenRetHome);
        }
      }
      else if ((x >= 145) && (x <= 169) && (y >= 72) && (y <= 96)) // return home min down
      {
        if (screenRetHome > 0)
        {
          screenRetHome = screenRetHome - 1;
          itoa(screenRetHome, char3, 10);
          myGLCD.setColor(255, 77, 0);
          if (screenRetHome >= 0 && screenRetHome <= 9) // Add a zero
          {
            myGLCD.setColor(0, 0, 0);
            myGLCD.fillRect(191, 59, 239, 75); // Clear previous value
          }
          myGLCD.setColor(255, 77, 0);
          myGLCD.print(char3, 191, 59);
          EEPROM.update(28, screenRetHome);
        }
      }
      else if ((x >= 145) && (x <= 169) && (y >= 110) && (y <= 134)) // Auto-dim level up by 1
      {
        if (screenDimLevel < 5)
        {
          screenDimLevel = (screenDimLevel + 1);
          EEPROM.update(29, screenDimLevel);
          itoa(screenDimLevel, char3, 10);
          myGLCD.setColor(255, 77, 0);
          myGLCD.print(char3, 191, 127);
        }
      }
      else if ((x >= 145) && (x <= 169) && (y >= 140) && (y <= 164)) // Auto-dim level down by 1
      {
        if (screenDimLevel > 0)
        {
          screenDimLevel = (screenDimLevel - 1);
          EEPROM.update(29, screenDimLevel);
          itoa(screenDimLevel, char3, 10);
          myGLCD.setColor(255, 77, 0);
          myGLCD.print(char3, 191, 127);
        }
      }
      else if ((x >= 145) && (x <= 169) && (y >= 178) && (y <= 202)) // Dim seconds up by 1
      {
        if (screenDimSec < 255)
        {
          screenDimSec = (screenDimSec + 1);
          EEPROM.update(30, screenDimSec);
          itoa(screenDimSec, char4, 10);
          myGLCD.setColor(255, 77, 0);
          myGLCD.print(char4, 191, 197);
        }
      }
      else if ((x >= 145) && (x <= 169) && (y >= 178) && (y <= 232)) // Dim seconds down by one
      {
        if (screenDimSec > 0)
        {
          screenDimSec = (screenDimSec - 1);
          EEPROM.update(30, screenDimSec);
          itoa(screenDimSec, char4, 10);
          myGLCD.setColor(255, 77, 0);
          myGLCD.print(char4, 191, 197);
        }
      }
      else if ((x >= 145) && (x <= 169) && (y >= 245) && (y <= 269)) // Brightness up by 1
      {
        if (screenBrightMem < 255)
        {
          screenBrightMem = (screenBrightMem + 1);
          EEPROM.update(31, screenBrightMem);
          itoa(screenBrightMem, char4, 10);
          myGLCD.setColor(255, 77, 0);
          myGLCD.print(char4, 187, 264);
        }
      }
      else if ((x >= 145) && (x <= 169) && (y >= 275) && (y <= 299)) // Brightness down by one
      {
        if (screenBrightMem > 2)
        {
          screenBrightMem = (screenBrightMem - 1);
          EEPROM.update(31, screenBrightMem);
          itoa(screenBrightMem, char4, 10);
          myGLCD.setColor(255, 77, 0);
          myGLCD.print(char4, 187, 264);
        }
      }

      break;

    case 17: // Lights Scheduling screen

      // ScheduleItem 1 = Lights On
      // ScheduleItem 2 = Lights Off
      myGLCD.setFont(f_arial_bold);

      // Set font color based on CO2 On, CO2 Off
      if (scheduleItem == 1) myGLCD.setColor(0, 255, 0);
      if (scheduleItem == 2) myGLCD.setColor(255, 0, 0);

      if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318)) // Schedule button
      {
        screenSchedule();
      }

      else if ((x >= 12) && (x <= 42) && (y >= 71) && (y <= 101)) // Lights On button
      {
        if (scheduleItem != 1) screenLights(1); // Switch to Lights On schedule
      }
      else if ((x >= 12) && (x <= 42) && (y >= 120) && (y <= 150)) // Lights Off button
      {
        if (scheduleItem != 2) screenLights(2); // Switch to Lights Off schedule
      }
      else if ((x >= 85) && (x <= 109) && (y >= 110) && (y <= 134)) // On hour up
      {

        if (scheduleItem == 1)
        {
          if (lights.onHour == 23) lights.onHour = 0;
          else lights.onHour = lights.onHour + 1;
          LightsHour = lights.onHour;
          EEPROM.update(328, LightsHour);
        }
        else if (scheduleItem == 2)
        {
          if (lights.offHour == 23) lights.offHour = 0;
          else lights.offHour = lights.offHour + 1;
          LightsHour = lights.offHour;
          EEPROM.update(329, LightsHour);
        }
        // Print to screen
        itoa(LightsHour, char3, 10);
        if (LightsHour >= 0 && LightsHour <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 120, 129);
      }
      else if ((x >= 85) && (x <= 109) && (y >= 140) && (y <= 164)) // On hour down
      {
        if (scheduleItem == 1)
        {
          if (lights.onHour == 0) lights.onHour = 23;
          else lights.onHour = lights.onHour - 1;
          LightsHour = lights.onHour;
          EEPROM.update(328, LightsHour);
        }
        else if (scheduleItem == 2)
        {
          if (lights.offHour == 0) lights.offHour = 23;
          else lights.offHour = lights.offHour - 1;
          LightsHour = lights.offHour;
          EEPROM.update(329, LightsHour);
        }

        // Print to screen
        itoa(LightsHour, char3, 10);
        if (LightsHour >= 0 && LightsHour <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 120, 129);

      }

      else if ((x >= 164) && (x <= 188) && (y >= 110) && (y <= 134)) // On min up
      {
        if (scheduleItem == 1)
        {
          if (lights.onMinute == 59) lights.onMinute = 0;
          else lights.onMinute = lights.onMinute + 1;
          LightsMinute = lights.onMinute;
          EEPROM.update(330, LightsMinute);
        }
        else if (scheduleItem == 2)
        {
          if (lights.offMinute == 59) lights.offMinute = 0;
          else lights.offMinute = lights.offMinute + 1;
          LightsMinute = lights.offMinute;
          EEPROM.update(331, LightsMinute);
        }
        // Print to screen
        itoa(LightsMinute, char3, 10);
        if (LightsMinute >= 0 && LightsMinute <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 199, 129);
      }
      else if ((x >= 164) && (x <= 188) && (y >= 140) && (y <= 164)) // On min down
      {
        if (scheduleItem == 1)
        {
          if (lights.onMinute == 0) lights.onMinute = 59;
          else lights.onMinute = lights.onMinute - 1;
          LightsMinute = lights.onMinute;
          EEPROM.update(330, LightsMinute);
        }
        else if (scheduleItem == 2)
        {
          if (lights.offMinute == 0) lights.offMinute = 59;
          else lights.offMinute = lights.offMinute - 1;
          LightsMinute = lights.offMinute;
          EEPROM.update(331, LightsMinute);
        }
        // Print to screen
        itoa(LightsMinute, char3, 10);
        if (LightsMinute >= 0 && LightsMinute <= 9) // add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 199, 129);
      }
      else if ((x >= 41) && (x <= 71) && (y >= 203) && (y <= 233)) // Schedule enable / disable
      {
        if (scheduleItem == 1)
        {
          if (ledEn.En) ledEn.En = false;
          else ledEn.En = true;
          myFiles.load(41, 203, 30, 30, schedActiveB[ledEn.En]);
          EEPROM.update(327, ledEn.En);
        }
      }

      break;

    case 18: // CO2 Scheduling screen

      // ScheduleItem 1 = CO2 On
      // ScheduleItem 2 = CO2 Off
      myGLCD.setFont(f_arial_bold);

      // Set font color based on CO2 On, CO2 Off
      if (scheduleItem == 1) myGLCD.setColor(0, 255, 0);
      if (scheduleItem == 2) myGLCD.setColor(255, 0, 0);

      if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318)) // Schedule button
      {
        screenSchedule();
      }

      else if ((x >= 12) && (x <= 42) && (y >= 71) && (y <= 101)) // CO2 On button
      {
        if (scheduleItem != 1) screenCO2(1); // Switch to CO2 On schedule
      }
      else if ((x >= 12) && (x <= 42) && (y >= 120) && (y <= 150)) // CO2 Off button
      {
        if (scheduleItem != 2) screenCO2(2); // Switch to CO2 Off schedule
      }
      else if ((x >= 85) && (x <= 109) && (y >= 110) && (y <= 134)) // On hour up
      {

        if (scheduleItem == 1)
        {
          if (co2.onHour == 23) co2.onHour = 0;
          else co2.onHour = co2.onHour + 1;
          Co2Hour = co2.onHour;
          EEPROM.update(333, Co2Hour);
        }
        else if (scheduleItem == 2)
        {
          if (co2.offHour == 23) co2.offHour = 0;
          else co2.offHour = co2.offHour + 1;
          Co2Hour = co2.offHour;
          EEPROM.update(334, Co2Hour);
        }
        // Print to screen
        itoa(Co2Hour, char3, 10);
        if (Co2Hour >= 0 && Co2Hour <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 120, 129);

      }
      else if ((x >= 85) && (x <= 109) && (y >= 140) && (y <= 164)) // On hour down
      {

        if (scheduleItem == 1)
        {
          if (co2.onHour == 0) co2.onHour = 23;
          else co2.onHour = co2.onHour - 1;
          Co2Hour = co2.onHour;
          EEPROM.update(333, Co2Hour);
        }
        else if (scheduleItem == 2)
        {
          if (co2.offHour == 0) co2.offHour = 23;
          else co2.offHour = co2.offHour - 1;
          Co2Hour = co2.offHour;
          EEPROM.update(334, Co2Hour);
        }
        // Print to screen
        itoa(Co2Hour, char3, 10);
        if (Co2Hour >= 0 && Co2Hour <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 120, 129);
      }

      else if ((x >= 164) && (x <= 188) && (y >= 110) && (y <= 134)) // On min up
      {

        if (scheduleItem == 1)
        {
          if (co2.onMinute == 59) co2.onMinute = 0;
          else co2.onMinute = co2.onMinute + 1;
          Co2Minute = co2.onMinute;
          EEPROM.update(335, Co2Minute);
        }
        else if (scheduleItem == 2)
        {
          if (co2.offMinute == 59) co2.offMinute = 0;
          else co2.offMinute = co2.offMinute + 1;
          Co2Minute = co2.offMinute;
          EEPROM.update(336, Co2Minute);
        }
        // Print to screen
        itoa(Co2Minute, char3, 10);
        if (Co2Minute >= 0 && Co2Minute <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 199, 129);
      }
      else if ((x >= 164) && (x <= 188) && (y >= 140) && (y <= 164)) // On min down
      {

        if (scheduleItem == 1)
        {
          if (co2.onMinute == 0) co2.onMinute = 59;
          else co2.onMinute = co2.onMinute - 1;
          Co2Minute = co2.onMinute;
          EEPROM.update(335, Co2Minute);
        }
        else if (scheduleItem == 2)
        {
          if (co2.offMinute == 0) co2.offMinute = 59;
          else co2.offMinute = co2.offMinute - 1;
          Co2Minute = co2.offMinute;
          EEPROM.update(336, Co2Minute);
        }
        // Print to screen
        itoa(Co2Minute, char3, 10);
        if (Co2Minute >= 0 && Co2Minute <= 9) // add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 199, 129);
      }
      else if ((x >= 51) && (x <= 81) && (y >= 203) && (y <= 233)) // Schedule enable / disable
      {
        if (co2En.En) co2En.En = false;
        else co2En.En = true;
        EEPROM.update(332, co2En.En);
        myFiles.load(51, 203, 30, 30, schedActiveB[co2En.En]);
      }

      break;

    case 19: // Circ Scheduling screen

      // ScheduleItem 1 = Circ On
      // ScheduleItem 2 = Circ Off
      myGLCD.setFont(f_arial_bold);

      // Set font color based on Circ On, Circ Off
      if (scheduleItem == 1) myGLCD.setColor(0, 255, 0);
      if (scheduleItem == 2) myGLCD.setColor(255, 0, 0);

      if ((x >= 107) && (x <= 129) && (y >= 294) && (y <= 318)) // Schedule button
      {
        screenSchedule();
      }

      else if ((x >= 12) && (x <= 42) && (y >= 71) && (y <= 101)) // Circ On button
      {
        if (scheduleItem != 1) screenCirc(1); // Switch to Circ On schedule
      }
      else if ((x >= 12) && (x <= 42) && (y >= 120) && (y <= 150)) // Circ Off button
      {
        if (scheduleItem != 2) screenCirc(2); // Switch to Circ Off schedule
      }
      else if ((x >= 85) && (x <= 109) && (y >= 110) && (y <= 134)) // On hour up
      {

        if (scheduleItem == 1)
        {
          if (circ.onHour == 23) circ.onHour = 0;
          else circ.onHour = circ.onHour + 1;
          CircHour = circ.onHour;
          EEPROM.update(338, CircHour);
        }
        else if (scheduleItem == 2)
        {
          if (circ.offHour == 23) circ.offHour = 0;
          else circ.offHour = circ.offHour + 1;
          CircHour = circ.offHour;
          EEPROM.update(339, CircHour);
        }
        // Print to screen
        itoa(CircHour, char3, 10);
        if (CircHour >= 0 && CircHour <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 120, 129);

      }
      else if ((x >= 85) && (x <= 109) && (y >= 140) && (y <= 164)) // On hour down
      {

        if (scheduleItem == 1)
        {
          if (circ.onHour == 0) circ.onHour = 23;
          else circ.onHour = circ.onHour - 1;
          CircHour = circ.onHour;
          EEPROM.update(338, CircHour);
        }
        else if (scheduleItem == 2)
        {
          if (circ.offHour == 0) circ.offHour = 23;
          else circ.offHour = circ.offHour - 1;
          CircHour = circ.offHour;
          EEPROM.update(339, CircHour);
        }
        // Print to screen
        itoa(CircHour, char3, 10);
        if (CircHour >= 0 && CircHour <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 120, 129);
      }

      else if ((x >= 164) && (x <= 188) && (y >= 110) && (y <= 134)) // On min up
      {

        if (scheduleItem == 1)
        {
          if (circ.onMinute == 59) circ.onMinute = 0;
          else circ.onMinute = circ.onMinute + 1;
          CircMinute = circ.onMinute;
          EEPROM.update(340, CircMinute);
        }
        else if (scheduleItem == 2)
        {
          if (circ.offMinute == 59) circ.offMinute = 0;
          else circ.offMinute = circ.offMinute + 1;
          CircMinute = circ.offMinute;
          EEPROM.update(341, CircMinute);
        }
        // Print to screen
        itoa(CircMinute, char3, 10);
        if (CircMinute >= 0 && CircMinute <= 9) // Add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 199, 129);
      }
      else if ((x >= 164) && (x <= 188) && (y >= 140) && (y <= 164)) // On min down
      {

        if (scheduleItem == 1)
        {
          if (circ.onMinute == 0) circ.onMinute = 59;
          else circ.onMinute = circ.onMinute - 1;
          CircMinute = circ.onMinute;
          EEPROM.update(340, CircMinute);
        }
        else if (scheduleItem == 2)
        {
          if (circ.offMinute == 0) circ.offMinute = 59;
          else circ.offMinute = circ.offMinute - 1;
          CircMinute = circ.offMinute;
          EEPROM.update(341, CircMinute);
        }
        // Print to screen
        itoa(CircMinute, char3, 10);
        if (CircMinute >= 0 && CircMinute <= 9) // add a zero
        {
          itoa(0, char3t, 10); // Make char3t 0
          strcat(char3t, char3);
          strcpy (char3, char3t);
        }
        myGLCD.print(char3, 199, 129);
      }
      else if ((x >= 51) && (x <= 81) && (y >= 203) && (y <= 233)) // Schedule enable / disable
      {
        if (circEn.En) circEn.En = false;
        else circEn.En = true;
        EEPROM.update(337, circEn.En);
        myFiles.load(41, 203, 30, 30, schedActiveB[circEn.En]);
      }

      break;
  }
}














