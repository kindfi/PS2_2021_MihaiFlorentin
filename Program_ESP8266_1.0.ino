#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>


/* define port */
WiFiClient client;
WiFiServer server(80);

/* WIFI settings */
const char* ssid = "Tenda_217C78";
const char* password = "";

/* data received from application */
String  data = "";
String abc = "Buna";
String command;

void setup()
{
  pinMode(0, INPUT);
  Serial.begin(9600);
  Serial1.begin(9600);

  /* start server communication */
  server.begin();
}

void loop()
{
  /* If the server available, run the "checkClient" function */
  client = server.available();
  if (!client) return;
  if (digitalRead(0) == HIGH) {
    command = "Card ACCEPTAT!";
  }
  else if (digitalRead(0) == LOW) {
    command = "Card RESPINS!";

  }
  data = checkClient ();
  Serial.print(data);

  if (Serial.available()) {

    abc = Serial.read();

    }

}




/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient (void)
{
  while (!client.available()) delay(1);
  String request = client.readStringUntil('\r');

  String s = "HTTP/1.1 200 OK\r\n";

  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n <link rel=\"icon\" href=\"data:;base64,=\"> <head> <title>Page Title</title> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <style> * { box-sizing: border-box; } body { font-family: Arial, Helvetica, sans-serif; margin: 0; } .header { padding: 80px; text-align: center; background: #1abc9c; color: white; } .header h1 { font-size: 40px; } .navbar { overflow: hidden; background-color: #333; position: sticky; position: -webkit-sticky; top: 0; } .navbar a { float: left; display: block; color: white; text-align: center; padding: 14px 20px; text-decoration: none; } .navbar a.right { float: right; } .navbar a:hover { background-color: #ddd; color: black; } .navbar a.active { background-color: #666; color: white; } .row { display: -ms-flexbox; /* IE10 */ display: flex; -ms-flex-wrap: wrap; /* IE10 */ flex-wrap: wrap; } .side { -ms-flex: 30%; /* IE10 */ flex: 30%; background-color: #f1f1f1; padding: 20px; } .main { -ms-flex: 70%; /* IE10 */ flex: 70%; background-color: white; padding: 20px; } .footer { padding: 20px; text-align: center; background: #ddd; } ";
  s += "media screen and (max-width: 700px) { .row { flex-direction: column; } } ";
  s += "media screen and (max-width: 400px) { .navbar a { float: none; width: 100%; } } </style> </head> <body> <div class=\"header\"> <h1>Proiect PS2</h1> <p>Florentin Mihai</p> </div> <div class=\"navbar\"> <a href=\"http://192.168.100.81\" class=\"active\">Home</a> <a href=\"A\">Start</a> <a href=\"S\">Stop</a> <a href=\"#\" class=\"right\">";
  s += command;
  s += "</a> </div> <div class=\"row\"> <div class=\"side\"> <h2>Componente</h2> <p> <ul> <li>Arduino Mega</li> <li>ESP8266-01</li> <li>HC-05 Bluetooth</li> <li>RFID RC522</li> <li>QTR-8RC</li> <li>Motors Shield</li> <li>Motors</li> <li>HC-SR04</li> <li>Fire</li> <li>Breadboarduri</li> <li>Carcasa masina</li> </ul> </p> </div> <div class=\"main\"> <h2>Functionalitati principale </h2> <p>Tema proiectului este un robotel ce poate intreprinde atat activitati automate cat si manuale. Prin urmare, robotelul poate fi controlat prin interfata web, pornind functia de urmarire automata a unei linii pe podea, sau, de asemenea, poate fi controlat manual prin bluetooth folosid aplicatia mobila dedicata.</p> <br> <h2>Alte functionalitati</h2><p>Ca si functionalitati secundare, robotelul poate citi carduri RFID atunci cand este setat in modul automat, identificand proprietarul dupa ID ul RFID-ului, mai apoi afisand in interfata web daca cardul a fost acceptat sau nu.</p><p>De asemenea, robotelul poate evita un obstacol iminent, folosind modulul ultrasonic, atunci cand este folosit in modul manual.</p><br><br><br><br><br><br> </div> </div> <div class=\"footer\"> <h5>Universitatea Politehnica Timisoara - Automatica si Calculatoare, Sectia Ingineria Sistemelor </h5> </div> </body> </html>\n";
  client.flush(); //clear previous info in the stream
  client.print(s); // Send the response to the client
  delay(1);

  request.remove(0, 5);
  request.remove(request.length() - 9, 9);
  return request;
}
/*******************************************************************************************************/
