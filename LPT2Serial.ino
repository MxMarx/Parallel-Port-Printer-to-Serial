/********************************************************************************
 * PrinterCaptureInterrupt.ino
 * ------------------
 * Monitor a parallel port printer output and capture each character. Output the 
 * character on the USB serial port so it can be captured in a terminal program.
 *
 * By............: Paul Jewell
 * Date..........: 29th January 2015
 * Version.......: 0.1a
 * Modification : Change Interrupt Routine so Arduino respond "faster" to Printer
 *                Writing Busy Signal directly from interrupt routine
 *                Ecirbaf 12 Jan 2017
 *                Test on a PC with a "generic Printer Text only" printer
 *                Printing a test page OK
 *                Even if using somme accent characters
 *                Depend How your Terminal Software is handling that.
 *-------------------------------------------------------------------------------
 * Wiring Layout
 * -------------
 * 
 * Parallel Port Output               Arduino Input
 * --------------------               -------------
 * Name      Dir.   Pin                Name    Pin
 * ----      ----   ---                ----    ---
 * nSTROBE    >       1................INT0      2 (as interupt)
 * DATA BYTE  >     2-9.......................3-10    
 * nACK       <      10.........................11
 * BUSY       <      11.........................12
 * OutofPaper <      12................GND
 * Selected   <      13.................5v
 * GND        <>  18-25................GND
 *-------------------------------------------------------------------------------
 ********************************************************************************/

int nStrobe = 2;
int Data0   = 3;
int Data1   = 4;
int Data2   = 5;
int Data3   = 6;
int Data4   = 7;
int Data5   = 8;
int Data6   = 9;
int Data7   = 10;
int nAck    = 11;
int Busy    = 12;
int led     = 13; // use as status led

enum States {
  READY,
  BUSY,
  ACK
} State;

  

void setup()
{
  // Configure pins
  pinMode(nStrobe, INPUT_PULLUP);
  
  for (int n = Data0; n < (Data7+1); n++)
    pinMode(n, INPUT_PULLUP);
  
  pinMode(nAck, OUTPUT);
  pinMode(Busy, OUTPUT);
  pinMode(led, OUTPUT);
  
  Serial.begin(19200);    // ** Actual com port could at least go this speed  ** //
  while (!Serial) {
    ;
  }
  

 attachInterrupt(0,Interrupt,FALLING);  // ** Name :Interrupt,  was clearer for me than DataReady  ** //


  State = READY;
  delay(100);
  Serial.println("Initialised");
}

void loop()
{
  switch (State) {
    case READY:
      digitalWrite(Busy, LOW);
      digitalWrite(nAck,HIGH);
      digitalWrite(led, HIGH);
      break;
      
  //    case BUSY: // nStrobe signal received by interrupt handler
  //      digitalWrite(Busy, HIGH);
  //      digitalWrite(led, LOW);
  //      ProcessChar();
  //      State = ACK;
  //      break;
  // ** All this case is made during Interrupt (Avoid some missed characters with "fast" printer) **
  
    case ACK:
      digitalWrite(nAck,LOW);
      delay(1); //milliseconds. Specification minimum = 5 us    ** Reduced to 1 is ok **
      State = READY;
      break;
  }   
}

void Interrupt()
{
    digitalWrite(Busy, HIGH);
    digitalWrite(led, LOW);
    ProcessChar();
    State = ACK;
}

void ProcessChar()
{
  byte Char;
  
  Char = digitalRead(Data0) +
         (digitalRead(Data1) << 1) +
         (digitalRead(Data2) << 2) +
         (digitalRead(Data3) << 3) +
         (digitalRead(Data4) << 4) +
         (digitalRead(Data5) << 5) +
         (digitalRead(Data6) << 6) +
         (digitalRead(Data7) << 7);
         
  Serial.print((char)Char);
}
