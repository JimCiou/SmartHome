SoftwareSerial esp8266(arx, atx);

String acmd;
void wifiInitial(Chain *ptrchain){
    esp8266.begin(ptrchain->baudRate);
    acmd="AT+CWJAP=\""+ptrchain->ssid+"\",\""+ptrchain->pass+"\"";
}

int wifi_State;

void wifiMain(){
  switch (wifi_State) {
    case 0: sendDebug("AT");                            //Working
        if (Loding("Sent AT")){ wifi_State++;}
        break;
    case 1: sendDebug("AT+CWMODE=3");                   //WiFi Mode: AT+CWMODE=3  (BOTH)
        if (Loding("AT+CWMODE=3")){ wifi_State++;}
        break;
    case 2: sendDebug(acmd);                            //Join Access Point: AT+CWJAP="SSID","Password"
        wifi_State++;
        if (Loding("Wifi connect")){ wifi_State++;}
        else{wifi_State--;}
        break;
    case 3: sendDebug("AT+CIFSR");                       //Get IP Address: AT+CIFSR
        if (Loding("Get ip address")){ wifi_State++;}
        else{wifi_State--;}
        break;
    case 4: sendDebug("AT+CIPMUX=1");                   //TCP/UDP Connections: AT+ CIPMUX=1  (Multiple)
         if (Loding("Set CIPMUX")){ wifi_State++;}
         else{wifi_State--;}
         break;
    case 5: sendDebug("AT+CIPSERVER=1,8888");            //Set as server: AT+ CIPSERVER= <mode>[,<port>]  (mode 1 to open; port = port)
         wifi_State++;
    break;
    case 6: if(esp8266.available()) {                     //Get connection!!
                if(esp8266.find("+IPD,")){                //Get Web connection!!
                    Serial.println("Get Connection...");
                    wifi_State++;}}
    break;
    case 7:
        delay(10);                                        //Read all the serial data
        //Subtract 48 because the read() function returns the ASCII decimal value and 0 (the first decimal number) starts at 4 ??(Not Sure)
        int connectionId = esp8266.read()-48; 

        //Advance cursor to "pin="
        esp8266.find("pin="); 

        //Get first number &  second number, example: the pin 13 then the 1st number is 1 multiply to 10, and 2nd number is 3.
        //The following packet extracted from the ProServer
        //47 45 54 20 2F 3F 70 69 6E 3D "31 30" 20 48 54 54 50 2F 31 2E 31 0D 0A 41 63 63 65 ...(GET /?pin="10" HTTP/1.1??Acce)
        //47 45 54 20 2F 3F 70 69 6E 3D "31 31" 20 48 54 54 50 2F 31 2E 31 0D 0A 41 63 63 65 ...(GET /?pin="11" HTTP/1.1??Acce)
        //47 45 54 20 2F 3F 70 69 6E 3D "31 32" 20 48 54 54 50 2F 31 2E 31 0D 0A 41 63 63 65 ...(GET /?pin="12" HTTP/1.1??Acce)
        int pinNumber = (esp8266.read()-48)*10; 
        pinNumber += (esp8266.read()-48); 

        //ON/OFF pin.
        digitalWrite(pinNumber, !digitalRead(pinNumber));     
        Serial.print("Turn Pin");
        Serial.print(pinNumber);
        Serial.print(":");
        Serial.print(digitalRead(pinNumber));
        Serial.println("!");
        
        //Close TCP / UDP connection: AT+CIPCLOSE=<id> or AT+CIPCLOSE
        String closeCommand = "AT+CIPCLOSE="; 
        closeCommand+=connectionId; // append connection id
        closeCommand+="\r\n";
        sendDebug(closeCommand);
        
        wifi_State--; 
        break;
  }
}

String get_response() {  
    String response="";  
    char c; 
    while (esp8266.available()) {  
        c=esp8266.read();
        response.concat(c);   
        delay(10);}
    response.trim();  
    return response;
}

boolean Loding(String state){
    String response=get_response();
    for (int timeout=0 ; timeout<30 ; timeout++){
        if(response.indexOf("OK") != -1 || response.indexOf("no change") != -1) {
            Serial.print(" OK ! ");
            if(timeout>=2){
                Serial.print("This commend waste ");
                Serial.print(timeout/2);
                Serial.println(" sec.");}
            else Serial.println("");
            return 1; 
            break;}
        else if(timeout==29){ //after 15 sec for wait esp without responce.
            Serial.print(state);
            Serial.println(" fail...\nExit2");
            return 0;}
        else{
          response=get_response(); //reget
          if(timeout==0) Serial.print("Wifi Loading.");
          else Serial.print(".");
          delay(500);
        }
    }
}

void sendDebug(String sent_cmd){
    Serial.print("SEND: ");
    Serial.println(sent_cmd);
    esp8266.println(sent_cmd);
} 
