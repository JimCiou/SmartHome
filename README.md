# SmartHome
Jim's arduino project 3(Smart Home). video is https://youtu.be/oK_ttDDY_Ac

Main Components:  Arduino R3, Wi-Fi Module(ESP8266) 1, LED 3, Resistance(220) 3  
Additional: USB to Serial TTL Module(FT232)  

Hint: This system is workable only in the single LAN, make sure Arduino and Web both depend in the same Wi-Fi router.
## Arduino part
- Check the baud rate of ESP8266 and change to 9600(suggest), then get the STAIP. Recommended to use FT232 and Terminal program(Realterm).
- The program "SmartHome_Debug.ino" can help to key-in AT-command by Arduino if you don't have FT232.
- Commands AT+CIPSTO9600 & AT+CIFSR are what we need.
- Include third-party functions into Lib folder, timer Lib is from https://github.com/JChristensen/Timer#installation.
- Fill up the hardware config in "toyPorting.ino" and build it!
```
#define aRX 4          /*Arduino's RX line pin, connect ESP8266's Tx*/
#define aTX 5          /*Arduino's TX line pin, connect ESP8266's Rx*/

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
```
##If there is necessary to update the EP8266's firmware, that must be needed FT232.

## Web part
- Modify IP setting in the 22nd line of "SmartHome_Web.html", reference to ESP8266's STAIP.
- Use your browser(Chrome or IE) execute "SmartHome_Web.html".
