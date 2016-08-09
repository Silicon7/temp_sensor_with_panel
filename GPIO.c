#include "main.h"

void GPIO_config(void)
{
    /*LEDS configure*/
    PORTCbits.RC0 = 0;
    LATCbits.LATC0 = 0;
    TRISCbits.RC0 = 0;
    PORTCbits.RC1 = 0;
    LATCbits.LATC1 = 0;
    TRISCbits.RC1 = 0;
    /*LEDC configure*/
    
    PORTCbits.RC6 = 0;
    LATCbits.LATC6 = 0;
    TRISCbits.RC6 = 0;
    PORTCbits.RC7 = 0;
    LATCbits.LATC7 = 0;
    TRISCbits.RC7 = 0;
    PORTCbits.RC5 = 0;
    LATCbits.LATC5 = 0;
    TRISCbits.RC5 = 0;
    
    PORTDbits.RD = 0x00;
    LATDbits.LATD = 0x00;
    TRISDbits.TRISD = 0x00;
    
    PORTBbits.RB = 0x00;
    LATBbits.LATB = 0x00;
    TRISBbits.TRISB = 0x00;
    
    PORTAbits.RA2 = 0;
    LATAbits.LA2 = 0;
    TRISAbits.TRISA2 = 1;
    
    /*BUTTONS*/

    TRISAbits.RA3 = 1;
    TRISAbits.RA4 = 1;
    TRISAbits.RA5 = 1;
    TRISEbits.RE0 = 1;

    /*buttons end*/
    
}
