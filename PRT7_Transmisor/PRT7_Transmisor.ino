/*
 * PROYECTO: Transmisor PRT-7 (Simulador)
 * TARGET:   Arduino (Cualquier placa, ej. UNO)
 */

void setup() {
  // Inicializa la comunicación serial a 9600 bits por segundo (Baud Rate)
  Serial.begin(9600);
  
  // Espera a que el monitor serial (o tu programa C++) se conecte.
  while (!Serial) {
    ; // esperar
  }
  
  // Imprime un mensaje de inicio en el monitor serial del Arduino
  Serial.println("--- Transmisor PRT-7 Iniciado ---");
  Serial.println("Enviando flujo de datos en 3 segundos...");
  delay(3000);
}


void loop() {
  // Flujo de datos del caso de estudio
  
  Serial.println("L,H");
  delay(1000);
  
  Serial.println("L,O");
  delay(1000);
  
  Serial.println("L,L");
  delay(1000);
  
  Serial.println("M,2");
  delay(1000);
  
  Serial.println("L,A");
  delay(1000);

  Serial.println("L,Space");
  delay(1000);
  
  Serial.println("L,W");
  delay(1000);
  
  Serial.println("M,-2");
  delay(1000);
  
  Serial.println("L,O");
  delay(1000);
  
  Serial.println("L,R");
  delay(1000);
  
  Serial.println("L,L");
  delay(1000);
  
  Serial.println("L,D");
  delay(1000);

  // --- Fin del flujo ---
  Serial.println("--- Flujo Terminado ---");
  
  // Nos detenemos aquí para no repetir el mensaje en bucle.
  while (true) {
    delay(10000); 
  }
}