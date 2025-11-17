#include <SoftwareSerial.h>
#include <Servo.h>

#define MOTORE_SX 11
#define MOTORE_DX 12

#define IR_DX 2  
#define IR_CT 3
#define IR_SX 4

#define BLACK 1
#define WHITE 0
#define luceVerdeSulSensore  0

Servo dx;
Servo sx;

  int rilievato011 = 0;
  int rilievato110 = 0;
  int partito = 0;
  int switchWait = 0;
  int i=0;//impone che 000 venga visualizzato 3 volte prima di eseguire la curva a 90°
  int j=0;//impone che 010 venga visualizzato 3 volte prima di resettare le varie variabili
  int temp;//serve per lo SWITCH nel caso 111.
  int stavoFacendoCurva = 0;//serve per lo SWITCH
  int secondaVolta000 = 0; //Non è ancora adoperato.
  int robotPosizionato = 0;

void setup() {
  //Serial.begin(19200); //communication rate for bluetooth
  Serial.begin(9600);//communication rate for console
  pinMode(IR_DX, INPUT);
  pinMode(IR_CT, INPUT);
  pinMode(IR_SX, INPUT); 

}

void muoviMotori(int motoreSinistro, int motoreDestro){
  motoreSinistro = 180 - motoreSinistro;
  sx.attach(MOTORE_SX);
  dx.attach(MOTORE_DX);
  sx.write(motoreSinistro);
  dx.write(motoreDestro);
  if (motoreSinistro == 90){
      sx.detach();}
  if (motoreDestro == 90){
    dx.detach();}
}

void testMotori(){
          Serial.println("180, 0");
        muoviMotori(180,0);
        delay(2000);
        Serial.println("170,10");
        muoviMotori(170,10);
        delay(2000);
        Serial.println("160,20");
        muoviMotori(160,20);
        delay(2000);
        Serial.println("150,30");
        muoviMotori(150,30);
        delay(2000);
        Serial.println("140,40");
        muoviMotori(140,40);
        delay(2000);
        Serial.println("130,50");
        muoviMotori(130,50);
        delay(2000);
        Serial.println("120,60");
        muoviMotori(120,60);
        delay(2000);
        Serial.println("110,70");
        muoviMotori(110,70);
        delay(2000);
        Serial.println("100,80");
        muoviMotori(100,80);
        delay(2000);
        //da qui in su i motori vanno in avanti
        Serial.println("90,90");
        muoviMotori(90,90);
        delay(2000);
        //da qui in giù i motori vanno all'indietro
        Serial.println("80,100");
        muoviMotori(80,100);
        delay(2000);        
        Serial.println("70,110");
        muoviMotori(70,110);
        delay(2000);
        Serial.println("60,120");
        muoviMotori(60,120);
        delay(2000);
        Serial.println("50,130");
        muoviMotori(50,130);
        delay(2000);
        Serial.println("40,140");
        muoviMotori(40,140);
        delay(2000);
        Serial.println("30,150");
        muoviMotori(30,150);
        delay(2000);
        Serial.println("20,160");
        muoviMotori(20,160);
        delay(2000);
        Serial.println("10,170");
        muoviMotori(10,170);
        delay(2000);
        Serial.println("0,180");
        muoviMotori(0,180);
        delay(2000);
  }

void loop() {

  if (partito == 0){
      int detectSX = digitalRead(IR_SX);
      int detectCT = digitalRead(IR_CT);
      int detectDX = digitalRead(IR_DX);
      int leggiSX = sx.read();
      int leggiDX = dx.read();
      const int cicli_I_perPartire = 6;
      Serial.print("i: ");
      Serial.print(i);
      Serial.print(" Sinistra: ");
      Serial.print(detectSX);
      Serial.print(" Centro: ");
      Serial.print(detectCT); 
      Serial.print(" Destra: ");
      Serial.print(detectDX); 
      Serial.print(" (BE)(");
      Serial.print(leggiSX);
      Serial.print(",");
      Serial.print(leggiDX);
      Serial.println(")");
      
      if (detectSX == 1 && detectCT == 1 && detectDX == 1){
        Serial.println("                                              (P01)");
        robotPosizionato = 1;
        muoviMotori(180,0);
      }
      
      if (detectSX == 0 && detectCT == 1 && detectDX == 0 && robotPosizionato == 1){
        Serial.println("                                              (R010)");
        muoviMotori(180,0);
        if (i<=cicli_I_perPartire){
          i++;
        }else{
          Serial.println("PARTITO ------------- 1");
          partito = 1;
        }
      }else{
        i == 0;
      }
      
      if (detectSX == 0 && detectCT == 0 && detectDX == 1 && robotPosizionato == 1){
        Serial.println("                                              (R001)");
        muoviMotori(180,5); 
        if (i<=cicli_I_perPartire){
          i++;
        }else{
          Serial.println("PARTITO ------------- 2");
          partito = 1;
        }
      }else{
        i == 0;
      }
      
      if (detectSX == 1 && detectCT == 0 && detectDX == 0 && robotPosizionato == 1){
        Serial.println("                                              (R100)");
        muoviMotori(175,0);
        if (i<=cicli_I_perPartire){
          i++;
        }else{
          Serial.println("PARTITO ------------- 3");
          partito = 1;
        }
      }else{
        i == 0;
      }

  }else{  
      int detectSX = digitalRead(IR_SX);
      int detectCT = digitalRead(IR_CT);
      int detectDX = digitalRead(IR_DX);
      int leggiSX = sx.read();
      int leggiDX = dx.read();
    
      Serial.print("i: ");
      Serial.print(i);
      Serial.print(" Sinistra: ");
      Serial.print(detectSX);
      Serial.print(" Centro: ");
      Serial.print(detectCT); 
      Serial.print(" Destra: ");
      Serial.print(detectDX); 
      Serial.print(" (BE)(");
      Serial.print(leggiSX);
      Serial.print(",");
      Serial.print(leggiDX);
      Serial.println(")");
     
        
      if (detectSX == 0 &&
          detectCT == 1 &&
          detectDX == 0){
            muoviMotori(180,0);
            stavoFacendoCurva=0;
            j++;
            if (j==3){
               Serial.println("Entrato in if [J = 3]");
               j=0;
               i=0;
               switchWait = 0;
               //rilievato110 = 0;
               //rilievato011 = 0;
            }
      }else if 
         (detectSX == 1 &&
          detectCT == 1 &&
          detectDX == 1){
            muoviMotori(180,0);
            //Se tutti i tre sensori si trovano sul nero, significa che l'angolo
            //è stato rilievato male per tutto il tempo: il robottino ha memorizzato
            //l'angolo (per esempio) 011.  Il programma memorizza l'angolo MA il robottino
            //si è mosso per tutto il tempo (anche se per pochi millisecondi) sulla linea
            //nera con DUE sensori posizionati sulla linea nera, mentre andava quasi in 
            //rettilineo. Nel momento in cui il robottino ha TRE sensori sulla linea nera,
            //confermiamo la frase precedente. 
            if (stavoFacendoCurva = 1){
                if (switchWait == 0){
                  switchWait = 1;
                  temp = rilievato011;
                  rilievato011 = rilievato110;
                  rilievato110 = temp;
                  Serial.print("[SWITCH EFFETTUATO] rilievato011: ");
                  Serial.print(rilievato011);
                  Serial.print(" rilievato110: ");
                  Serial.println(rilievato110);
                }
            }
      }else if
         (detectSX == 0 &&
          detectCT == 1 &&
          detectDX == 1){
            rilievato110 = 0;
            rilievato011 = 1;
            Serial.println("Rilievato011"); 
            muoviMotori(180,5); 
            stavoFacendoCurva = 1;
      }else if 
         (detectSX == 0 &&
          detectCT == 0 &&
          detectDX == 1){
            stavoFacendoCurva = 1;
            muoviMotori(100,40);
            //rilievato110 = 0;
            //rilievato011 = 0;
      }else if
         (detectSX == 1&&
          detectCT == 1 &&
          detectDX == 0){
            rilievato110 = 1;
            rilievato011 = 0;
            Serial.println("Rilievato110"); 
            muoviMotori(175,0);
            stavoFacendoCurva = 1;
     }else if
         (detectSX == 1 &&
          detectCT == 0 &&
          detectDX == 0){
            muoviMotori(140,80);
            stavoFacendoCurva = 1;
            //rilievato110 = 0;
            //rilievato011 = 0; 
     }else if
          ((detectSX == 0 &&
           detectCT == 0 &&
           detectDX == 0)){       
            i++;
            if (i == 3){
                i=0;
                secondaVolta000=0;
                Serial.println("Entrato in if [i = 3]");
                int valoreSensoriUniti = digitalRead(IR_SX)*100 + digitalRead(IR_CT)*10 + digitalRead(IR_DX);//serve per rendere più comprensibili le condizioni a seguire.
                if (rilievato011 == 1){   
                    while (valoreSensoriUniti != 10)//fino a quando il robot non si trova sulla linea
                    {  
                        valoreSensoriUniti = digitalRead(IR_SX)*100 + digitalRead(IR_CT)*10 + digitalRead(IR_DX);          
                        Serial.print("Entrato in if 011. ValoreSensoriUniti = ");
                        Serial.println(valoreSensoriUniti);
                        muoviMotori(70,50);
                    }
                    rilievato011=0; //reset della variabile. MOLTO IMPORTANTE: evita molti errori nel campo
                    //In seguito il robot viene riassestato. La curva a 90 infatti può durare più del previsto. Quando il robot ferma la curva è già a 110 o 001.
                    valoreSensoriUniti = digitalRead(IR_SX)*100 + digitalRead(IR_CT)*10 + digitalRead(IR_DX); 
                    while (valoreSensoriUniti != 10)
                    {  
                    valoreSensoriUniti = digitalRead(IR_SX)*100 + digitalRead(IR_CT)*10 + digitalRead(IR_DX);   
                    muoviMotori(140,80);
                    }
                }else if (rilievato110 == 1){         
                    while (valoreSensoriUniti != 10)
                    {
                        valoreSensoriUniti = digitalRead(IR_SX)*100 + digitalRead(IR_CT)*10 + digitalRead(IR_DX); 
                        Serial.print("Entrato in if 110. ValoreSensoriUniti = ");
                        Serial.println(valoreSensoriUniti);
                        muoviMotori(140,120);
                    }
                    
                    rilievato110=0;
                    valoreSensoriUniti = digitalRead(IR_SX)*100 + digitalRead(IR_CT)*10 + digitalRead(IR_DX); 
                    while (valoreSensoriUniti != 10)
                    { 
                     valoreSensoriUniti = digitalRead(IR_SX)*100 + digitalRead(IR_CT)*10 + digitalRead(IR_DX);              
                     muoviMotori(100,40); 
                    }
                    }
                }else{secondaVolta000++;}
           }         
  }
}
