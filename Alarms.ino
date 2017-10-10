void updateAlarms()
{

  // Clear, free, delete all possible alarms
  for (byte i = 0; i <= 40; i++)
  {
    Alarm.free(i);
  }

  // Reset Arduino every day at midnight
  Alarm.alarmRepeat(23, 59, 0, software_Reset);

  // Power On alarms
  if (ledEn.En)
  {
    Alarm.alarmRepeat(lights.onHour, lights.onMinute, 0, AlarmPwrLights_On);
    Alarm.alarmRepeat(lights.offHour, lights.offMinute, 0, AlarmPwrLights_Off);
  }
  if (co2En.En)
  {
    Alarm.alarmRepeat(co2.onHour, co2.onMinute, 0, AlarmPwrCO2_On);
    Alarm.alarmRepeat(co2.offHour, co2.offMinute, 0, AlarmPwrCO2_Off);
  }
  if (circEn.En)
  {
    Alarm.alarmRepeat(circ.onHour, circ.onMinute, 0, AlarmPwrCirc_On);
    Alarm.alarmRepeat(circ.offHour, circ.offMinute, 0, AlarmPwrCirc_Off);
  }

  // Dosing alarms
  if (pump1.Sun == 1)
  {
    Alarm.alarmRepeat(dowSunday, pump1.onHour, pump1.onMinute, 0, Alarmpump1Pump);
  }
  if (pump2.Sun == 1)
  {
    Alarm.alarmRepeat(dowSunday, pump2.onHour, pump2.onMinute, 0, Alarmpump2Pump);
  }
  if (pump3.Sun == 1)
  {
    Alarm.alarmRepeat(dowSunday, pump3.onHour, pump3.onMinute, 0, Alarmpump3Pump);
  }
  if (pump1.Mon == 1)
  {
    Alarm.alarmRepeat(dowMonday, pump1.onHour, pump1.onMinute, 0, Alarmpump1Pump);
  }
  if (pump2.Mon == 1)
  {
    Alarm.alarmRepeat(dowMonday, pump2.onHour, pump2.onMinute, 0, Alarmpump2Pump);
  }
  if (pump3.Mon == 1)
  {
    Alarm.alarmRepeat(dowMonday, pump3.onHour, pump3.onMinute, 0, Alarmpump3Pump);
  }
  if (pump1.Tue == 1)
  {
    Alarm.alarmRepeat(dowTuesday, pump1.onHour, pump1.onMinute, 0, Alarmpump1Pump);
  }
  if (pump2.Tue == 1)
  {
    Alarm.alarmRepeat(dowTuesday, pump2.onHour, pump2.onMinute, 0, Alarmpump2Pump);
  }
  if (pump3.Tue == 1)
  {
    Alarm.alarmRepeat(dowTuesday, pump3.onHour, pump3.onMinute, 0, Alarmpump3Pump);
  }
  if (pump1.Wed == 1)
  {
    Alarm.alarmRepeat(dowWednesday, pump1.onHour, pump1.onMinute, 0, Alarmpump1Pump);
  }
  if (pump2.Wed == 1)
  {
    Alarm.alarmRepeat(dowWednesday, pump2.onHour, pump2.onMinute, 0, Alarmpump2Pump);
  }
  if (pump3.Wed == 1)
  {
    Alarm.alarmRepeat(dowWednesday, pump3.onHour, pump3.onMinute, 0, Alarmpump3Pump);
  }
  if (pump1.Thu == 1)
  {
    Alarm.alarmRepeat(dowThursday, pump1.onHour, pump1.onMinute, 0, Alarmpump1Pump);
  }
  if (pump2.Thu == 1)
  {
    Alarm.alarmRepeat(dowThursday, pump2.onHour, pump2.onMinute, 0, Alarmpump2Pump);
  }
  if (pump3.Thu == 1)
  {
    Alarm.alarmRepeat(dowThursday, pump3.onHour, pump3.onMinute, 0, Alarmpump3Pump);
  }
  if (pump1.Fri == 1)
  {
    Alarm.alarmRepeat(dowFriday, pump1.onHour, pump1.onMinute, 0, Alarmpump1Pump);
  }
  if (pump2.Fri == 1)
  {
    Alarm.alarmRepeat(dowFriday, pump2.onHour, pump2.onMinute, 0, Alarmpump2Pump);
  }
  if (pump3.Fri == 1)
  {
    Alarm.alarmRepeat(dowFriday, pump3.onHour, pump3.onMinute, 0, Alarmpump3Pump);
  }
  if (pump1.Sat == 1)
  {
    Alarm.alarmRepeat(dowSaturday, pump1.onHour, pump1.onMinute, 0, Alarmpump1Pump);
  }
  if (pump2.Sat == 1)
  {
    Alarm.alarmRepeat(dowSaturday, pump2.onHour, pump2.onMinute, 0, Alarmpump2Pump);
  }
  if (pump3.Sat == 1)
  {
    Alarm.alarmRepeat(dowSaturday, pump3.onHour, pump3.onMinute, 0, Alarmpump3Pump);
  }
}

// Alarm handlers
void AlarmPwrFan_On()
{
  stctime = millis();
  digitalWrite(pwrFanPin, LOW);
  globalPower.pwrFan = true;
  FanStatus = true;
  if (dispScreen == 1) myFiles.load(178, 155, 24, 24, pwrFanIconS[globalPower.pwrFan]); // Update home screen
  Serial.println(F("Fan on"));
  if (webbypass == false)
  {
    web = 9;
    websection();
  }
}

void AlarmPwrFan_Off()
{
  digitalWrite(pwrFanPin, HIGH);
  globalPower.pwrFan = false;
  FanStatus = false;
  if (dispScreen == 1) myFiles.load(178, 155, 24, 24, pwrFanIconS[globalPower.pwrFan]); // Update home screen
  Serial.println(F("Fan off"));
  if (webbypass == false)
  {
    web = 9;
    websection();
  }
}

void AlarmPwrHeater_On()
{
  stctime = millis();
  digitalWrite(pwrHeaterPin, LOW);
  globalPower.pwrHeater = true;
  HeaterStatus = true;
  if (dispScreen == 1) myFiles.load(178, 189, 24, 24, pwrHeatIconS[globalPower.pwrHeater]); // Update home screen
  Serial.println(F("Heater on"));
  if (webbypass == false)
  {
    web = 9;
    websection();
  }
}

void AlarmPwrHeater_Off()
{
  stctime = millis();
  digitalWrite(pwrHeaterPin, HIGH);
  globalPower.pwrHeater = false;
  HeaterStatus = false;
  if (dispScreen == 1) myFiles.load(178, 189, 24, 24, pwrHeatIconS[globalPower.pwrHeater]); // Update home screen
  Serial.println(F("Heater off"));
  if (webbypass == false)
  {
    web = 9;
    websection();
  }
}

void AlarmPwrCO2_On()
{
  digitalWrite(pwrCO2Pin, LOW);
  globalPower.pwrCO2 = true;
  CO2Status = true;
  if (dispScreen == 1) myFiles.load(206, 155, 24, 24, pwrCO2IconS[globalPower.pwrCO2]); // update home screen
  Serial.println(F("CO2 on"));
  if (webbypass == false)
  {
    web = 9;
    websection();
  }
}

void AlarmPwrCO2_Off()
{
  digitalWrite(pwrCO2Pin, HIGH);
  globalPower.pwrCO2 = false;
  CO2Status = false;
  if (dispScreen == 1) myFiles.load(206, 155, 24, 24, pwrCO2IconS[globalPower.pwrCO2]); // Update home screen
  Serial.println(F("CO2 off"));
  if (webbypass == false)
  {
    web = 9;
    websection();
  }
}

void AlarmPwrLights_On()
{
  digitalWrite(pwrLightsPinLED, LOW);
  globalPower.pwrLights = true;
  LightsStatus = true;
  if (dispScreen == 1) myFiles.load(178, 121, 24, 24, pwrLightIconS[globalPower.pwrLights]); // Update home screen
  Serial.println(F("Lights on"));
  if (webbypass == false)
  {
    web = 9;
    websection();
  }
}

void AlarmPwrLights_Off()
{
  digitalWrite(pwrLightsPinLED, HIGH);
  globalPower.pwrLights = false;
  LightsStatus = false;
  if (dispScreen == 1) myFiles.load(178, 121, 24, 24, pwrLightIconS[globalPower.pwrLights]); // Update home screen
  Serial.println(F("Lights off"));
  if (webbypass == false)
  {
    web = 9;
    websection();
  }

}

void AlarmPwrCirc_On()
{
  //  Serial.println(F("Circ on"));
  digitalWrite(pwrCircPin, LOW);
  globalPower.pwrCirc = true;
  CircStatus = true;
  if (dispScreen == 1) myFiles.load(206, 121, 24, 24, pwrCircIconS[globalPower.pwrCirc]); // Update home screen
  Serial.println(F("Circ on"));
}

void AlarmPwrCirc_Off()
{
  digitalWrite(pwrCircPin, HIGH);
  globalPower.pwrCirc = false;
  CircStatus = false;
  if (dispScreen == 1) myFiles.load(206, 121, 24, 24, pwrCircIconS[globalPower.pwrCirc]); // Update home screen
  Serial.println(F("Circ off"));
}


void Alarmpump1Pump()
{
  doseAmt1 = EEPROM.readFloat(201); // Read dose amount 1

  // Update tank volume
  vol1 = EEPROM.readFloat(213);
  vol1 = (vol1 - doseAmt1);
  EEPROM.updateFloat(213, vol1);
  EEPROM.update(19, 1);

  Serial.print("Pump1 ok");
  Serial.print("\n");

  //Operate Pump
  pumpTime1 = doseAmt1 * 1010; // Convert ml to ms
  analogWrite(pump1Pump, 0);
  delay(pumpTime1); // Delay while the motor runs
  analogWrite(pump1Pump, 255);

  if (dispScreen == 1) checkDosing(); // Update home screen
  if (webbypass == false)
  {
    web = 9;
    websection();
  }
}

void Alarmpump2Pump()
{
  doseAmt2 = EEPROM.readFloat(205); // Read dose amount 2

  // Update tank volume
  vol2 = EEPROM.readFloat(217);
  vol2 = (vol2 - doseAmt2);
  EEPROM.updateFloat(217, vol2);
  EEPROM.update(20, 1);

  Serial.print("Pump2 ok");
  Serial.print("\n");

  //Operate Pump
  pumpTime2 = doseAmt2 * 1010; // Convert ml to ms
  analogWrite(pump2Pump, 0);
  delay(pumpTime2); // Delay while the motor runs
  analogWrite(pump2Pump, 255);

  if (dispScreen == 1) checkDosing(); // Update home screen
  if (webbypass == false)
  {
    web = 9;
    websection();
  }
}

void Alarmpump3Pump()
{
  doseAmt3 = EEPROM.readFloat(209); // Read dose amount 3

  // Update tank volume
  vol3 = EEPROM.readFloat(221);
  vol3 = (vol3 - doseAmt3);
  EEPROM.updateFloat(221, vol3);
  EEPROM.update(21, 1);

  Serial.print("Pump3 ok");
  Serial.print("\n");

  //Operate Pump
  pumpTime3 = doseAmt3 * 1010; // Convert ml to ms
  analogWrite(pump3Pump, 0);
  delay(pumpTime3); // Delay while the motor runs
  analogWrite(pump3Pump, 255);

  if (dispScreen == 1) checkDosing(); // Update home screen
  if (webbypass == false)
  {
    web = 9;
    websection();
  }
}














