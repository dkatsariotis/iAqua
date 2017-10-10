void checkTemp() // Called from the main loop to update temperature reading
{
  sensors.requestTemperatures(); // Send the command to get temperatures
  tempC = sensors.getTempCByIndex(0); // 0 refers to the first IC on the wire

  dtostrf(tempC, 4, 1, tempstring);  // Convert to string

  if (tempC > -127) intTempC = (tempC * 10); // Create an integer var of the temp

  if (intTempC > (STCTemp * 10)) // Turn on fan if over threshold
  {

    if (!globalPower.pwrFan)
    {
      AlarmPwrFan_On(); // Turn on Fan
    }
    if (globalPower.pwrHeater)
    {
      AlarmPwrHeater_Off(); // Turn off heater
    }

  }

  if ((intTempC == (STCTemp * 10)) && (millis() >= (stctime + 60000))) // Turn fan and heater off when temp drops below setting
  {

    if (globalPower.pwrHeater)
    {
      AlarmPwrHeater_Off(); // Turn off heater
    }
    if (globalPower.pwrFan)
    {
      AlarmPwrFan_Off(); // Turn off Fan
    }
  }

  if (intTempC <= ((STCTemp * 10) - 10)) // Turn heater on when temp drops below setting
  {

    if (globalPower.pwrFan)
    {
      AlarmPwrFan_Off(); // Turn off fan
    }

    if (!globalPower.pwrHeater)
    {
      AlarmPwrHeater_On(); // Turn on heater
    }

  }

  //Backup Check - relay fail over
  if (intTempC >= ((STCTemp * 10) + 20)) // Turn on fan if over threshold
  {

    Serial.println(F("Fan failure"));

    if (millis() >= (stctime + 120000))
    {
      if (globalPower.pwrFan)
      {
        AlarmPwrFan_Off(); // Turn off Fan
        delay(2000);
        AlarmPwrHeater_On(); // Turn on heater
      }
    }

  }


  // Draw temp to screen
  myGLCD.setFont(f_arial_bold);

  if (intTempC > -127) // Display Temp only if value is available
  {
    myGLCD.print(tempstring, 132, 64);
  }
  else
    myGLCD.print(0, 132, 64);
}



