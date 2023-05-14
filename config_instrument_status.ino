boolean config_instrument_status(byte instrument_no){
      
  lcd.print(instrument_no);
  lcd.print(":");
  if((instrument_data_in=="ON")){
      
      if(instrument_no==1){
        Serial.println("Main ON");//main supply is given to the controller
        digitalWrite(starting_instrument_pin + instrument_no -1,LOW);
      }
      else if(instrument_no==6){
        digitalWrite(12,HIGH);
        Serial.println("BL ON");
        lcd.print("ON ");
      }
      else{
        Serial.print(instrument_no);
        Serial.println(F(" ON."));
        lcd.print("ON ");
        digitalWrite(starting_instrument_pin + instrument_no -1,LOW);//AS THE RELAY IS IN ACTIVE LOW, IT WILL MAKE IT ON 
      }
      return 1;
  }
  else if(instrument_data_in=="OFF"){
      if(instrument_no==1){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Main Supply is");
        lcd.setCursor(0,1);
        lcd.print("OFF");
        Serial.println("CUT OFF");//main suppply is tranfered to th physical board
        if(get_instrument_status(start_instrument6_keyword,end_instrument6_keyword,sizeof(start_instrument6_keyword),2000)){
                      config_instrument_status(6);
        }
        //If main supply will off then we don't need to keep on any other relay 
        for(byte i=0;i<no_of_ins;i++){
             digitalWrite(starting_instrument_pin+i,HIGH);
        }
        //Now before prompting all other just check the lcd backlight status
        
         return 0;
      }
      else if(instrument_no==6){
        digitalWrite(12,LOW);
        lcd.print("OFF ");
        Serial.println("BL OFF");//BL for back Light
      }
      else{
        Serial.print(instrument_no);
        Serial.println(" OFF.");
        lcd.print("OFF ");
        digitalWrite(starting_instrument_pin + instrument_no -1,HIGH);
      }
      return 1;
     
  }
  else{
      
      Serial.println("match-X");
      return 0;
      
  }
  
}

