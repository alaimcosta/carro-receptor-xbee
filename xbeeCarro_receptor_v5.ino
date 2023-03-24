//RECEPTOR
#include<XBee.h>
#include<SoftwareSerial.h>

XBee xbee = XBee();
SoftwareSerial XBEE2(2,3);


//  --- Mapeamento das portas logicas
int dado = 0;       //Armazena dados seriais que entram
//  --- Mapeamento das portas logicas
int ENA = 5;
int ENB = 6;
const int IN2 = 4;
const int IN3 = 7;
const int IN4 = 8;
const int IN1 = 9;

// --- Inicialização ---
void setup() {
  Serial.begin(9600);  
  for (int i = 5; i < 10; i++) {
    pinMode(i, OUTPUT);  // inicializa os pinos digital de 5 a 9 como saída
  }
  XBEE2.begin(9600);
  xbee.begin(Serial);  
  
}

void loop() {
  if(XBEE2.available() > 0) {
    char dado = XBEE2.read();  // Lê os dados da porta serial
    if(dado == '1'){
      rotacaoNormal();
    } else if (dado == '2') {  // botão acionado
      recuarCarro();
    } else if (dado == '3') {  // botão acionado
      giraRight();
    } else if (dado == '4') {  // botão acionado
      giraLeft();
    } else if(dado == '0'){
      pararMotor();
    }   
  }
  Serial.flush();
  }

  
// --- Funções Auxiliares
void rotacaoNormal() {  // rotate para frente com menor rotação
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  analogWrite(ENA, 100);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENB, 100);
}
void recuarCarro() {  //função para voltar
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  analogWrite(ENA, 100);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(ENB, 100);
}
void pararMotor() {
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW);
}
void giraRight() {  //ROTAÇÃO PARA DIREITA
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 100);  //ENA motor lado direito
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 100);  //ENB motor lado esquerdo
}
void giraLeft() {  //ROTAÇÃO PARA LEFT
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 100);  //ENA motor lado direito
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 100);  //ENB motor lado esquerdo
}
