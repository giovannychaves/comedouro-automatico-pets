#include <DS3231.h>  
DS3231  rtc(SDA, SCL);
Time t;

int horaAtual, minutoAtual;

int horaAlimentacao1, minutoAlimentacao1, demosComida1;

int horaAlimentacao2, minutoAlimentacao2, demosComida2;

void setup()
{ 
  
 rtc.begin(); 
 Serial.begin(115200); 

 pinMode(8, OUTPUT);
 pinMode(12, OUTPUT);
 
 horaAlimentacao1 = 10; 
 minutoAlimentacao1 = 00;

 horaAlimentacao2 = 18; 
 minutoAlimentacao2 = 00;

 //0 = não e 1 = sim
 demosComida1 = 0;   
 demosComida2 = 0; 
 
  // Código para setar o horário correto no relógio apenas 1 vez
  // rtc.setDate(21,5,2022);    // determina a data (dia, mes, ano)
  // rtc.setDOW(SATURDAY);     // determina o dia da semana
  // rtc.setTime(15, 32, 0);     // determina o horário (hora, minuto, segundo)

  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);

} 

void loop()
{
  t = rtc.getTime();
  horaAtual = t.hour;
  minutoAtual = t.min;

  if (horaAtual == horaAlimentacao1 && minutoAtual == minutoAlimentacao1 && demosComida1 == 0 ){

    digitalWrite(8, LOW);
    delay(10000);
    digitalWrite(8, HIGH);
    demosComida1 = 1;
    
  }

    if (horaAtual == horaAlimentacao2 && minutoAtual == minutoAlimentacao2 && demosComida2 == 0 ){

    digitalWrite(8, LOW);
    delay(10000);
    digitalWrite(8, HIGH);
    demosComida2 = 1;
    
  }

  if (demosComida1 == 0 || demosComida1 == 1 && demosComida2 == 1 ){
    Serial.print("Horário atual: ");
    Serial.println(rtc.getTimeStr());
    Serial.print("Próxima alimentação: ");
    Serial.print(horaAlimentacao1);
    Serial.print("h:");
    Serial.print(minutoAlimentacao1);
    Serial.println("min");
    Serial.println("  ");
  }

  if (demosComida1 == 1 && demosComida2 == 0){
     Serial.print("Horário atual: ");
    Serial.println(rtc.getTimeStr());
    Serial.print("Próxima alimentação: ");
    Serial.print(horaAlimentacao2);
    Serial.print("h:");
    Serial.print(minutoAlimentacao2);
    Serial.println("min");
    Serial.println("  ");
  }
 
  if (horaAtual == 0 && minutoAtual == 0){
    demosComida1 = 0;
    demosComida2 = 0; 
  }
 
  delay (1000);
} 
