
/*    
 *  THIS IS AN HOME AUTOMATION PROJECT USING ARDUINO AND ESP32
 *  OGBONNA JOSEPH PROJECT DIRECTION    
 *  PROJECT NAME : HOME AUTOMAATION 
 *  
 *  THIS PROJECT IS BASED ON CONTROLLING BASIC HOME APPLIANCES VIA THE INTERNET,
 *  A WEB PAGE IS CREATED TO HANDLE THE HTTP RESPONSE......
 */


#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "........";
const char* password = "........";


char homepage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
   <head>
      <meta name="viewport" content="width=device=width, initial-scale=1\">
      <title>HOME AUTOMATION</title>
      <style>
        html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background-color: rgba(120, 112, 228, 0.911);}
        body{margin-top: 50px;}
        h1{ margin: 50px auto 30px; font-size: 37px; font-family: fantasy}
        h3{margin-bottom: 20px; font-family: Tahoma}
        h4{margin-top: 20px; font-size: 20px; font-family: Tahoma}
        .button{background-color:blue; border-radius: 10px; block-size: 30pt; }
        footer{font-size: 15px; color: blue;}
      </style>
      
    </head>
  <body>
    <h1>HOME AUTOMATION WITH ARDUINO AND ESP32 </h1>
    <h3>THIS IS A SIMPLE AUTOMATION PROJECT THAT IS USED TO CONTROL LIGHT BULBS USING WIFI CONNECTION</h3>
    <h4>THE LIGHT BULB DATA WILL BE SENT TO THE THINGSPEAK IOT PLATFORM</h4>
    <p id="bulb1">BULD STATUS : OFF</p>
    <a href="#"><button type="button" class="button button-on redclr" onclick="onbulb1()"> .ON</button></a>
    <a href="#"><button type="button" class="button button-off" onclick="offbulb1()">OFF</button></a>
    <p id="bulb2">BULB STATUS : OFF</p>
    <a href="#"><button type="button" class="button button-on greenclr" onclick="onbulb2()"> .ON</button></a>
    <a href="#"><button type="button" class="button button-off" onclick="offbulb2()">OFF</button></a>
    <p id="bulb3">BULB STATUS : OFF</p>
    <a href="#"><button type="button" class="button button-on greenclr" onclick="onbulb3()"> .ON</button></a>
    <a href="#"><button type="button" class="button button-off" onclick="offbulb3()">OFF</button></a>
    <p id="bulb4">BULB STATUS : OFF</p>
    <a href="#"><button type="button" class="button button-on relayclr" onclick="onbulb4()"> .ON</button></a>
    <a href="#"><button type="button" class="button button-off" onclick="offbulb4()">OFF</button></a>
    <br>
    <br>
    <br>
    <footer>
        <B>AUTOMATION BY JOSEPH</B>
        <script>
                function onbulb1(){document.getElementById("bulb1").innerHTML="BULB STATUS : ON"};
                function onbulb2(){document.getElementById("bulb2").innerHTML="BULB STATUS : ON"};
                function onbulb3(){document.getElementById("bulb3").innerHTML="BULB STATUS : ON"};
                function onbulb4(){document.getElementById("bulb4").innerHTML="BULB STATUS : ON"};
                function offbulb1(){document.getElementById("bulb1").innerHTML="BULB STATUS : OFF"};
                function offbulb2(){document.getElementById("bulb2").innerHTML="BULB STATUS : OFF"};
                function offbulb3(){document.getElementById("bulb3").innerHTML="BULB STATUS : OFF"};
                function offbulb4(){document.getElementById("bulb4").innerHTML="BULB STATUS : OFF"};
                
              </script>
    </footer>
  </body>
  </html>)=====";


WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
