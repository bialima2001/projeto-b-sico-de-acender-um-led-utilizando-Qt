#define LED 13

int status = 0; // variavel criada para veificar o status do led, 1 para aceso ou 0 para apagado

const String ledAceso = "LED1"; // utilizei  palavra LED1 para o comando emitido pelo Qt de ligar o led

const String ledApagado = "LED0"; // palavra LED0 para o comando emitido pelo Qt de desligar o led

void setup() {
  
    pinMode(LED, OUTPUT); // definindo o pino 13 como saida

    Serial.begin(115200); // iniciando o monitor serial com 115200 bits/segundos, mesmo valor utilizado no Qt

}
 
void loop() {
  
    if(Serial.available()>0){ // retorna o número de bbits disponivel para leitura na serial, ou seja se for >0, tem algo pra ler
      String linha = Serial.readStringUntil('\n'); //lendo do monitor serial até o \n e salvando na string linha
      if(linha.startsWith("{") && linha.endsWith("}")){ // testa se a string começa com'{' e termina com '}', caso isso seja verdadeiro, então trata-se do pacote enviado pelo Qt
        if(linha.indexOf(ledAceso)!=-1){ // retorna a posição de dado caractere ou string dentro de outra string, retorna -1 se o caractere ou string n existir dentro dessa outra string
          //ou seja, se na linha lida do serial conter LED1, então: 
          digitalWrite (LED, HIGH); // liga o led
          status = 1; // seta o status do led como ligado
        }
        if(linha.indexOf(ledApagado)!=-1){ // se na linha lida do serial conter LED0, então
          digitalWrite (LED, LOW); // desliga o led
          status = 0; // seta o status do led como desligado
        }
      }
    }
    
    if(status == 1){ // se o led estiver ligado
      Serial.print("{"+ledAceso+"}"); // escreve na serial "{LED1}", ou seja, envia o pacote
    }else{// se não
      Serial.print("{"+ledApagado+"}");// escreve na serial "{LED0}"
    }
    delay(100);// espera um pouquinho 
}
 

