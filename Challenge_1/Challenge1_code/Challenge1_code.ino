
void setup(){}
/*=======================================================================*/
void segm7(uint8_t digit) //update the 7-segment indicator function
{
  switch (digit) 
  {
  case 0:
    //Mask: --BAFGEDC.
    PORTD = 0b11101110;   
    break;
  case 1:
    PORTD = 0b10000010;  
    break;
  case 2:
    PORTD = 0b11011100;
    break;
  case 3:
    PORTD = 0b11010110;
    break;
  case 4:
    PORTD = 0b10110010;
    break;
  case 5:
    PORTD = 0b01110110;
    break;
  case 6:
    PORTD = 0b01111110;
    break;
  case 7:
    PORTD = 0b11000010;
    break;
  case 8:
    PORTD = 0b11111110;
    break;
  case 9:
    PORTD = 0b11110110;
    break;
  default:
    PORTD = 0x00;
    break;
  }
}

/*=======================================================================*/
void loop()
{
  
  DDRD = 0xff;              //set all pins in PORTD as output
  PORTD = 0x00;             //set all pins in PORTD in LOW logical level
  
  while(1)            
  {
   for(uint8_t i=0; i<10; i++)
   {
     segm7(i);              //update the 7-segment indicator display
     delay(1000);           //wait 1 second
   }
  }
  
}
