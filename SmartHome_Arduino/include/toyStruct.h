typedef struct {
  int controlPin1;   /*Control Pin for electric equipment 1*/
  int controlPin2;   /*Control Pin for electric equipment 2*/
  int controlPin3;   /*Control Pin for electric equipment 3*/
} ControlPin;

typedef struct {
  int moniPort;          /*Port for monitor*/
  int baudRate;          /*Baud rate of ESP8266*/
  String ssid;           /*Account of Wi-Fi Router*/
  String pass;           /*Password of Wi-Fi Router*/
  ControlPin controlPin; /*{electric equipment 1, electric equipment 2, electric equipment 3}*/
} Chain;