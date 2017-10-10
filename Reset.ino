void firstRunSetup()
{

  // Set default screen settings
  EEPROM.update(28, 1); // Return home
  EEPROM.update(29, 5); // Auto dim level
  EEPROM.update(30, 5); // Auto dim seconds
  EEPROM.update(31, 180); // Brightness if no auto dim

  // Set default heater values
  EEPROM.update(18, 26); // 18 // Fan on temp

  // Set default dosing values
  EEPROM.update(201, 0);   // 201 - 204 // Dose 1 0.0 mL
  EEPROM.update(202, 0);
  EEPROM.update(203, 0);
  EEPROM.update(204, 0);
  EEPROM.update(205, 0);   // 205 - 208 // Dose 2 0.0 mL
  EEPROM.update(206, 0);
  EEPROM.update(207, 0);
  EEPROM.update(208, 0);
  EEPROM.update(209, 0);   // 209 - 212 // Dose 3 0.0 mL
  EEPROM.update(210, 0);
  EEPROM.update(211, 0);
  EEPROM.update(212, 0);
  EEPROM.update(213, 0);   // 213 - 216 // Resevior 1 remaining volume 0 ml
  EEPROM.update(214, 0);
  EEPROM.update(215, 0);
  EEPROM.update(216, 0);
  EEPROM.update(217, 0);   // 217- 220 // Resevior 2 remaining volume 0 ml
  EEPROM.update(218, 0);
  EEPROM.update(219, 0);
  EEPROM.update(220, 0);
  EEPROM.update(221, 0); // 221 - 224 // Resevior 3 remaining volume 0 ml
  EEPROM.update(222, 0);
  EEPROM.update(223, 0);
  EEPROM.update(224, 0);
  EEPROM.update(225, 250); // 225 // Resevior 1 capacity 250 mL
  EEPROM.update(226, 250); // 226 // Resevior 2 capacity 250 mL
  EEPROM.update(227, 250); // 227 // Resevior 3 capacity 250 mL
  EEPROM.update(300, 0);
  EEPROM.update(301, 0);
  EEPROM.update(302, 0);
  EEPROM.update(303, 0);
  EEPROM.update(304, 0);
  EEPROM.update(305, 0);
  EEPROM.update(306, 0);
  EEPROM.update(307, 0);
  EEPROM.update(308, 0);
  EEPROM.update(309, 0);
  EEPROM.update(310, 0);
  EEPROM.update(311, 0);
  EEPROM.update(312, 0);
  EEPROM.update(313, 0);
  EEPROM.update(314, 0);
  EEPROM.update(315, 0);
  EEPROM.update(316, 0);
  EEPROM.update(317, 0);
  EEPROM.update(318, 0);
  EEPROM.update(319, 0);
  EEPROM.update(320, 0);
  EEPROM.update(321, 0);
  EEPROM.update(322, 0);
  EEPROM.update(323, 0);
  EEPROM.update(324, 0);
  EEPROM.update(325, 0);
  EEPROM.update(326, 0);
  EEPROM.update(327, 0);
  EEPROM.update(328, 0);
  EEPROM.update(329, 0);
  EEPROM.update(330, 0);
  EEPROM.update(331, 0);
  EEPROM.update(332, 0);
  EEPROM.update(333, 0);
  EEPROM.update(334, 0);
  EEPROM.update(335, 0);
  EEPROM.update(336, 0);
  EEPROM.update(337, 0);
  EEPROM.update(338, 0);
  EEPROM.update(339, 0);
  EEPROM.update(340, 0);
  EEPROM.update(341, 0);

}














