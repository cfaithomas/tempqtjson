#include <ArduinoJson.h>
int ledPin=3;
String inputString = "";
boolean stringComplete = false;
int state=0; //etat de la led

StaticJsonDocument<255> doc; //variable de type Statijsondocument 255 taille max document json

void setup() {
    Serial.begin(9600); //ouvre le port serie 9600
    pinMode(ledPin,OUTPUT); //pin en mode sortie

}

void loop() {
    while (Serial.available()) {
        char inChar = (char)Serial.read();  // lecture octet par octet stockage dans un char:
        inputString += inChar;              // ajout dans la chaine provisoire
        if (inChar == '}') {               // si } fin du json
            stringComplete = true;          // la chaine est complète
            break;                          //casse la boucle
        }
    }

    if (stringComplete){
        DeserializationError error = deserializeJson(doc, inputString); //met la chaine json dans le doc

        if (error) { //si erreur
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }
        state=doc["button"]; //recupere la valeur de la clé button

        inputString = "";  //on remet la chaine à blanc
    }

    digitalWrite(ledPin, state); //on ecrit sur la pin la valeur de state


}
