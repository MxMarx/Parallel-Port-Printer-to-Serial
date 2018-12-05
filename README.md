# Parallel-Port-Printer-to-Serial
  PrinterCaptureInterrupt.ino
  
  Monitor a parallel port printer output and capture each character. Output the
  
  character on the USB serial port so it can be captured in a terminal program.
  
 
  By............: Paul Jewell
  
  Date..........: 29th January 2015
  
  Version.......: 0.1a
  
  Modification : Change Interrupt Routine so Arduino respond "faster" to Printer
  
                 Writing Busy Signal directly from interrupt routine
                 
                 Ecirbaf 12 Jan 2017
                 
                 Test on a PC with a "generic Printer Text only" printer
                 
                 Printing a test page OK
                 
                 Even if using somme accent characters
                 
                 Depend How your Terminal Software is handling that.
                 
