//RECEPTOR
//Importação das bibliotecas a serem utilizadas
#include<XBee.h>
//Realizarem comunicação serial com o módulo Xbee
#include<SoftwareSerial.h>

XBee xbee = XBee();
//Incicializa um construtor da biblioteca SoftwareSerial
//Cria um objeto XBEE2, passando as portas 2 e 3 para comunicação serial
SoftwareSerial XBEE2(2,3);


//  --- Mapeamento das portas logicas
int dado = 0;//Armazena dados seriais que entram
int ENA = 5; //porta para ativar motor right
int ENB = 6; //porta para ativar motor left
const int IN2 = 4;
const int IN3 = 7;
const int IN4 = 8;
const int IN1 = 9;

// --- Inicialização ---
void setup() {
  //definimos o baudrate em 9600
  Serial.begin(9600);  
  for (int i = 5; i < 10; i++) {
    pinMode(i, OUTPUT);  // inicializa os pinos digitais de 5 a 9 como saída
  }
  //Iniciamos a porta XBEE2 responsável por enviar as informações
  //para o módulo Xbee e definimos o taxa de transmissão(baudrate) de 9600
  XBEE2.begin(9600);
  xbee.begin(Serial);  
}

void loop() {
  //verifica se existe algum dado disponível na porta de comunicação serial do Xbee
  if(XBEE2.available() > 0) {
    char dado = XBEE2.read();// Lê os dados da porta serial
    if(dado == '1'){ //se dado for 1 chama a função rotacaoNormal
      rotacaoNormal();
    } else if (dado == '2') {//se dado for 2 chama a função recuarCarro
      recuarCarro();
    } else if (dado == '3') {//se dado for 3 chama a função giraRight
      giraRight();
    } else if (dado == '4') {//se dado for 4 chama a função giraLeft
      giraLeft();
    } else if(dado == '0'){//se dado for 0 chama a função pararMotor
      pararMotor();
    }   
  }
  Serial.flush(); //instrução que permite a conclusão da transmissão de dados 
                  //da porta serial
  }

// --- Funções Auxiliares
void rotacaoNormal() {  // rotate para frente
  digitalWrite(IN1, HIGH); //motor right
  digitalWrite(IN2, LOW); //motor right
  analogWrite(ENA, 100);//Define a velocidade é ativa o motor right. Variar de
                        // 0 a 255, onde 255 é a velocidade máxima.
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 100);
}
void recuarCarro() {  //função para voltar
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 100);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 100);
}
void pararMotor() {
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW);
}
void giraRight() {  //ROTAÇÃO PARA DIREITA
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 100); 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 100);
}
void giraLeft() {  //ROTAÇÃO PARA LEFT
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 100);  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 100);  
}
