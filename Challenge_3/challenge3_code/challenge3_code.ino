uint8_t i = 0;  // variable for the counter

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
//Starts timer1
void tim1_start(uint16_t numb_16b)
{
  TCCR1A = 0;                 //control register of timer1

  TCNT1 = 0;                  // timer/counter value
  OCR1A = numb_16b;           //the TOP value of the timer1

  TIMSK1 = 0;                 // Clear Timer Interrupt Mask Register
  TIMSK1 |= (1 << OCIE1A);    //interrupt enable

  TCCR1B = 0;                 // Clear timer/counter control register B
  TCCR1B |= (1 << WGM12)      // CTC mode
         | (1 << CS12);       //set prescaller to 256
}
/*=======================================================================*/
//Starts timer1
void tim2_start(uint8_t numb_8b)
{
  TCCR2A = 0;                                // Clear timer setings register
  TCCR2A |= (1 << COM2A1)                    // Clear OC2A on Compare Match, set OC2A at BOTTOM,(non-inverting mode)
            | (1 << WGM21) | (1 << WGM20);   // Set FastPWM mode

  TCNT2 = 0;                                 //clear counter register
  OCR2A = numb_8b;                           //output compare register A

  TCCR2B = 0 ;// Clear rimer/counter control register B
  TCCR2B |= (1 << CS22); //set prescaler to 64
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
  OCR2A =(uint8_t)(255.0*(i/9.0));// new value for output compare register A
}
/*=======================================================================*/
void loop()
{

  DDRD = 0xff;              //set all pins in PORTD as output
  PORTD = 0x00;             //set all pins in PORTD in LOW logical level

  DDRB |= (1<<DDB3);        // OUTPUT pin 11

  tim1_start(62500);
  tim2_start(0);            //tuning on PWM on OC2A 

  sei();                    //enable all interrupts
  while (1)
  {
    //do nothing
  }

}
