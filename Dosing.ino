void checkDosing() // Updates dosing info on home screen
{
  char char3[4];  // Used to convert int to char
  char char4[4];
  char char5[4];

  vol1 = EEPROM.readFloat(213); // Read the remaining volume for pump 1 in ml
  vol2 = EEPROM.readFloat(217); // Read the remaining volume for pump 2 in ml
  vol3 = EEPROM.readFloat(221); // Read the remaining volume for pump 3 in ml

  doseAmt1 = EEPROM.readFloat(201); // Dose 1 amount in mL
  doseAmt2 = EEPROM.readFloat(205); // Dose 2 amount in mL
  doseAmt3 = EEPROM.readFloat(209); // Dose 3 amount in mL

  doseCap1 = EEPROM.read(225); // Tank 1 capacity in ml
  doseCap2 = EEPROM.read(226); // Tank 2 capacity in ml
  doseCap3 = EEPROM.read(227); // Tank 3 capacity in ml

  doses1 = (vol1 / doseAmt1); // Calculate tank 1 doses left
  doses2 = (vol2 / doseAmt2); // Calculate tank 2 doses left
  doses3 = (vol3 / doseAmt3); // Calculate tank 3 doses left

  // Set initial Y values of an empty reservoir
  float y1pump1 = 212;
  float y1pump2 = 212;
  float y1pump3 = 212;

  // Calculate percentage left and generate the y1 coordinate for drawing the fill levels
  if (doses1 > 0) y1pump1 = 213 - ((vol1 / doseCap1) * 55); // Tank 1
  if (doses2 > 0) y1pump2 = 213 - ((vol2 / doseCap2) * 55); // Tank 2
  if (doses3 > 0) y1pump3 = 213 - ((vol3 / doseCap3) * 55); // Tank 3

  // Clear previous data on screen with black
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(20, 158, 84, 212);

  // Values to center remaining dose numerical values over tubes on screen
  int xcharPump1 = 17;
  int xcharPump2 = 43;
  int xcharPump3 = 69;
  if (doses1 <= 99) xcharPump1 = 20;
  if (doses1 <= 99) xcharPump2 = 46;
  if (doses1 <= 99) xcharPump3 = 72;
  if (doses1 <= 9) xcharPump1 = 24;
  if (doses1 <= 9) xcharPump2 = 50;
  if (doses1 <= 9) xcharPump3 = 76;

  // Draw remaining dose numerical values
  myGLCD.setFont(f_sinclair_S);

  myGLCD.setColor(255, 255, 255);

  itoa(doses1, char3, 10);
  myGLCD.print(char3, xcharPump1, 135);

  myGLCD.setColor(255, 255, 255);

  itoa(doses2, char4, 10);
  myGLCD.print(char4, xcharPump2, 135);

  myGLCD.setColor(255, 255, 255);

  itoa(doses3, char5, 10);
  myGLCD.print(char5, xcharPump3, 135);

  // Draw empty fert tubes
  myFiles.load(15, 155, 23, 65, "1ferts.raw");
  myFiles.load(41, 155, 23, 65, "1ferts.raw");
  myFiles.load(67, 155, 23, 65, "1ferts.raw");

  // Draw fert fill
  myGLCD.setColor(255, 0, 0);  // Red for tank 1
  myGLCD.fillRect(20, y1pump1, 32, 213);
  myGLCD.setColor(0, 255, 0);  // Green for tank 2
  myGLCD.fillRect(46, y1pump2, 58, 213);
  myGLCD.setColor(0, 0, 255);  // Blue for tank 3
  myGLCD.fillRect(72, y1pump3, 84, 213);

}


