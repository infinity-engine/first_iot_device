void instrument(){
  const char no_AP[]="No AP";
  const char keyword_OK[]="OK";
  esp.print("AT+CWJAP?\r\n");
  //now check if the esp is busy or not,
  if (esp_read_until(busy,sizeof(busy),1000,500)){
        //Hold on for a few second then send a at command
        Serial.println(F("Busy"));
        dump_esp();
        delay(20000);
        esp.print("AT\r\n");
        if (esp_read_until(keyword_OK,sizeof(keyword_OK),5000,500)){
            Serial.println(F("Esp check Fine"));
            delay(200);
            esp.print("AT+CWJAP?\r\n");
        }
           
        else{
           //oh no! now you have to reset the hardware interrupt of esp
           Serial.println(F("Esp Hardware RESET"));
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("ESP RESET");
           digitalWrite(9,LOW);
           delay(200);
           //here thing is i could give it to high again but its 5v so, declaring the pin 9 will do remove the connection from it
           //that's fine
           digitalWrite(9,HIGH);
           delay(40000);
           dump_esp();
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("RESET DONE");
           delay(2000);
           lcd.clear();
           esp.print("AT+CWJAP?\r\n");
        }
   }
    
  if (!esp_read_until(no_AP,sizeof(no_AP),2000,500))
    Serial.println(F("Connected to Wifi"));
  else{
    Serial.println(F("It's not connected to wifi, delay for attempting again"));
    dump_esp();
    delay (1000);
    esp.print("AT+CWJAP?\r\n");
    if (esp_read_until(keyword_OK,sizeof(keyword_OK),5000,1000)){
      Serial.println(F("NOW its connected"));
    }
    else
      esp_setup();
      delay(3000);
  }
  dump_esp();
  char instrument_url[]="GET http://connectionmakeeasy.tk/data_fetch.php?channel_id=1069&read_key=oNbTMghgrSgzEZCa\r\n\r\n";
  const char keyword_fetch_ok[]="Fetch OK";
  if(esp_connect(sizeof(instrument_url))){
     if(get_package(instrument_url)){
        if(esp_read_until(keyword_fetch_ok,sizeof(keyword_fetch_ok),10000,8000)){
               if(get_instrument_status(start_instrument1_keyword,end_instrument1_keyword,sizeof(start_instrument1_keyword),4000)){
                      config_instrument_status(1);
                      if(get_instrument_status(start_instrument2_keyword,end_instrument2_keyword,sizeof(start_instrument2_keyword),3000)){
                          lcd.clear();lcd.setCursor(0,0);
                          config_instrument_status(2);
                          if(get_instrument_status(start_instrument3_keyword,end_instrument3_keyword,sizeof(start_instrument3_keyword),3000)){
                                
                                config_instrument_status(3);
                                if(get_instrument_status(start_instrument4_keyword,end_instrument4_keyword,sizeof(start_instrument4_keyword),3000)){
                              
                                      config_instrument_status(4);
                                      if(get_instrument_status(start_instrument5_keyword,end_instrument5_keyword,sizeof(start_instrument5_keyword),3000)){
                                           lcd.setCursor(0,1);
                                           config_instrument_status(5);
                                           if(get_instrument_status(start_instrument6_keyword,end_instrument6_keyword,sizeof(start_instrument6_keyword),3000)){
                                               config_instrument_status(6);
                                               
                                           }
                                               
                                      }
                                          
                                  }
                               
                              }
  
                               
                        }
                      
                            
                }
            }
               
      
    }
 
 }
 dump_esp();
}

