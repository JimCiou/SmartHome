#define arx 4          /*Arduino's RX line pin, connect ESP8266's Tx*/
#define atx 5          /*Arduino's TX line pin, connect ESP8266's Rx*/

Chain Porting(void){
   /*Please full up the index to customize your product*/
   Chain toyChain {
      9600,            /*Port for monitor*/
      9600,            /*Baud rate of ESP8266*/
      "IOT_2.4G",      /*Account of Wi-Fi Router*/
      "iot250st",      /*Password of Wi-Fi Router*/
      {10,11,12},      /*{electric equipment 1, electric equipment 2, electric equipment 3}*/
    };
    /*Please full up the index to customize your product*/
    return toyChain;
}

