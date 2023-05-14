boolean get_instrument_status(char start_key[],char end_key,int sizeof_keyword,int timeout){
  unsigned long time_start;
  char data_in[20];
  time_start=millis();
  sizeof_keyword--;
  //check whether the any data available or not
  for(byte b=0;b<sizeof_keyword;b++){
       while(!esp.available()){
         if(millis()>=(time_start+timeout)){
           Serial.println(F("Timeout 3"));
           return 0;
         }
       }
       data_in[b]=esp.read();
       
  }

  int pr_time = 200;
  //check for the keyword
  while(1){
    
    for(byte b=0;b<sizeof_keyword;b++){
      unsigned long int pr_start = millis();
      while(!esp.available()){
        if((millis() >= (pr_start+pr_time))||(millis()>=(time_start+timeout)))
           break;
      }
      if(data_in[b]!=start_key[b])
        break;
      else if (b==(sizeof_keyword-1)){
        instrument_data_in="";
        Serial.println("match");
        for(byte i=0;i<=5;i++){
          unsigned long int pr_start = millis();
          while(!esp.available()){
             if((millis() >= (pr_start+pr_time))||(millis()>=(time_start+timeout)))
                break;
          }
          char c=esp.read();
          //Serial.print(c);
          if ( c == end_key){
            //Serial.println("e key");//end key
            return 1;
            
          }
          instrument_data_in += c;
        }
        return 1;
      }
        
    }
    if(esp.overflow()){
         Serial.print("OF");//overflow
       }

    //Rolling the buffer
    for(byte b=0;(b<(sizeof_keyword-1));b++){
       data_in[b]=data_in[b+1];
    }
    unsigned long int pr_start = millis();
    while(!esp.available()){
        if((millis() >= (pr_start+pr_time))||(millis()>=(time_start+timeout)))
           break;
    }  
    data_in[sizeof_keyword-1]=esp.read();
    
    //timeout control
    if (millis()>=(time_start+timeout)){
        Serial.println("Timeout 4");
        return 0;
    }
    
  }
 
  
}
           

  
