boolean esp_setup()
{
  dump_esp();
  const char keyword_OK[] = "OK";
  const char no_AP[] = "No AP";
  esp.print("AT\r\n");
  if (esp_read_until(keyword_OK, sizeof(keyword_OK), 5000, 500))
    Serial.println(F("Esp check OK"));
  else
  {
    Serial.println(F("Esp check fail"));
    esp.print("AT+RST\r\n");
    if (esp_read_until(keyword_OK, sizeof(keyword_OK), 10000, 500))
      Serial.println(F("Esp RESET OK"));
    else
    {
      Serial.println(F("Esp RESET"));
      return 0;
    }
    return 0;
  }

  dump_esp();

  esp.print("AT+CWMODE=1\r\n");
  if (esp_read_until(keyword_OK, sizeof(keyword_OK), 5000, 500))
    Serial.println(F("AT+CWMODE check OK"));
  else
  {
    Serial.println(F("AT+CWMODE check fail"));
    return 0;
  }

  dump_esp();
  esp.print("AT+CWJAP?\r\n");
  // Now check whether it is connected to wifi or not
  if (!esp_read_until(no_AP, sizeof(no_AP), 2000, 1000))
  {
    Serial.println(F("Connected to Wifi"));
  }
  else
  {
    dump_esp();
    Serial.println(F("It's not connected to wifi"));
    esp.print("AT+CWJAP=\"XXXX\",\"XXXXX\"\r\n");
    if (esp_read_until(keyword_OK, sizeof(keyword_OK), 10000, 5000))
      Serial.println(F("Esp is connected to Wifi Station."));
    else
    {
      Serial.println(F("Wifi connection failed."));
      return 0;
    }
  }

  dump_esp();

  esp.print("AT+CIPMUX=0\r\n");
  if (esp_read_until(keyword_OK, sizeof(keyword_OK), 5000, 500))
    Serial.println(F("AT+CIPMUX=0 check OK"));
  else
  {
    Serial.println(F("AT+CIPMUX=0 check fail"));
    return 0;
  }

  dump_esp();

  return 1;
}
