uint8_t i = 0;  //variable for the counter

void setup() {}
/*=======================================================================*/
void segm7(uint8_t digit) //update the 7-segment indicator display function
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
//Starts timer1
void tim1_start(uint16_t numb_16b)
{
  TCCR1A = 0;                     // Clear timer/counter control register

  TCNT1 = 0;                      // timer/counter value
  OCR1A = numb_16b;               //the TOP value of the timer1

  TIMSK1 = 0;                     // Clear Timer Interrupt Mask Register
  TIMSK1 |= (1 << OCIE1A);        //interrupt enable

  TCCR1B = 0;                     // Clear timer/counter control register B
  TCCR1B |= (1 << WGM12)          // CTC mode
            | (1 << CS12);           //set prescaller to 256
}

/*=======================================================================*/
//Interrupt service routine for timer 1
ISR(TIMER1_COMPA_vect)
{
  segm7(i);       //update the 7-segment indicator display
  if (i < 9) {    // counter from 0 to 9
    i++;
  } else {
    i = 0;
  }
}
/*=======================================================================*/
void loop()
{
  DDRD = 0xff;              //set all pins in PORTD as output
  PORTD = 0x00;             //set all pins in PORTD in LOW logical level

  tim1_start(62500);        //set the timer1 to work with 1 second period


  sei();                    //enable all interrupts
  while (1)
  {
    //do nothing
  }

}
