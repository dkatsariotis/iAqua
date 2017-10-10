void websection() {

  STCTempInt = STCTemp;
  cmd = false;
  webbypass = false;
  heaterval = false;
  fanval = false;
  co2val = false;
  lightsval = false;
  doses1Int = doses1;
  doses2Int = doses2;
  doses3Int = doses3;

  row_values *row = NULL;

  Ethernet.maintain();

start:

  if (conn.connected()) {
    //Serial.println(F(web));

    switch (web)

    {

      case 1:

        sprintf(ddate, "'%02u-%02u-%02u'", year(), month(), day());
        sprintf(ttime, "'%02u:%02u:%02u'", hour(), minute(), second());
        sprintf(query, INSERT_DATA, tempstring, ddate, ttime);
        //Serial.println(F(query));
        //Serial.println(F("Sending live data to MySQL..."));
        cur.execute(query);

        //Serial.println(F("Live Data updated."));

        cur.close();
        //        conn.close();

        break;

      case 2:
        //Serial.println(F("Getting commands from MySQL..."));

        sprintf(query, SELECT_CONTROL_CMD);
        //Serial.println(query);
        cur.execute(query);

        // Here we get a value from the database and use it.


        // Now we read the rows.
        cur.get_columns();

        do {
          row = cur.get_next_row();
          // We use the first value returned in the row
          if (row != NULL) {
            lightsval = atol(row->values[0]);
            //Serial.println(lightsval);
            co2val = atol(row->values[1]);
            //Serial.println(co2val);
            fanval = atol(row->values[2]);
            //Serial.println(fanval);
            heaterval = atol(row->values[3]);
            //Serial.println(heaterval);
            cmd = atol(row->values[4]);
            //Serial.println(cmd);
          }
        } while (row != NULL);
        cur.close();


        if (cmd == true)
        {
          webbypass = true;
          Serial.println(F("Remote cmd execute"));
          if (lightsval == true) {

            if (LightsStatus == false) AlarmPwrLights_On();
          }
          else if (lightsval == false) {

            if (LightsStatus == true) AlarmPwrLights_Off();
          }

          if (co2val == true) {

            if (CO2Status == false) AlarmPwrCO2_On();
          }
          else if (co2val == false) {

            if (CO2Status == true) AlarmPwrCO2_Off();
          }

          if (fanval == true) {

            if (FanStatus == false) AlarmPwrFan_On();
          }
          else if (fanval == false) {

            if (FanStatus == true) AlarmPwrFan_Off();
          }

          if (heaterval == true) {

            if (HeaterStatus == false) AlarmPwrHeater_On();
          }
          else if (heaterval == false) {

            if (HeaterStatus == true) AlarmPwrHeater_Off();
          }

          sprintf(query, UPDATE_CONTROL_CMD);
          //Serial.println(F(query));
          cur.execute(query);
          cur.close();
          webbypass = false;
          goto updatestatus;
        }

        //Serial.println(F("Commands retrieved."));

        break;

      case 9:

updatestatus:
        sprintf(query, UPDATE_CONTROL, LightsStatus, CO2Status, FanStatus, HeaterStatus, STCTempInt, doses1Int, doses2Int, doses3Int);
        Serial.println(query);
        Serial.println(F("Sending status data to MySQL..."));
        cur.execute(query);

        cur.close();
        //conn.close();
        Serial.println(F("Status data updated."));

        break;


    }

  }


  else {
    Serial.println(F("Connection failed."));
    Serial.println(F("Disconnecting old connection..."));
    cur.close();
    conn.close();
    Serial.println(F("Reconnecting to MySQL..."));
    conn.connect(server_addr, 3306, user, password);
    goto start;
  } // end if (client)

}


// Web Section end














