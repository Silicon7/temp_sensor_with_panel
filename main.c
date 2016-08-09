#include "main.h"

void alarm(long x);

char array1[6];
char display_ram[6];
char display_ram2[6];
char display_ram3[2];
char display_ram4[6];
const char seg_data[6] = {1,2,3,4,5,6};
const char opened[6] = {0,20,14,21,14,13};
const char SHORT[5] = {5,22,23,24,25};
const char rtn[6] = {24,14,25,26,24,21};
const char adjust[6] = {10,13,28,26,5,25};
const char high_alarm_off[5] = {16,8,4,2,1};
const char low_alarm_off[5] = {1,2,4,8,16};
const unsigned char seg_select[6] = {0xF8,0xF4,0xEC,0xDC,0xBC,0x7C};
const char digits[29] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0x7F,0x9C,0x89,0xC7,0x8C,0xC8,0x8B,0xA3,0xAF,0x87,0xC1,0xFF,0xE1};
char decimal,decimal4;

int low_LTP=1900, low_HTP=2000, high_LTP=2500, high_HTP=2600;

static unsigned long SUM = 0;
unsigned long sum_display;
static char off_count;
static char alarm_state=0;
//static int abd,abd1;



int main()
{
    int i,get,state,p_state=-1;
    signed double c;
    double m;
    signed long temp;
    unsigned char temp_check;
    static char tmsec=0;
   // static char press_up=1 , panel_state=-1 , press_A3=1;
    
    m = 0.004526679784;
    c = -1879.101778669170;
    
    GPIO_config();
    TIMER2_config();
    ADC_config();
    while(1)
    {
        if(LATCbits.LATC0)
        {
            tmsec++;
            if(tmsec == 5){
                tmsec=0;
            sum_display = SUM;
            SUM = 0;
           // abd1 = abd;
           // abd=0;
            temp = m*sum_display + c;
            temp_check = temp/100;
           // LATCbits.LATC6 = 1;
            get = division(temp);
           // LATCbits.LATC6 = 0;
            
            switch(p_state)
            {
                case 0:
                      if(temp<0 || temp>7000)
                    {
                        state = -1;
                        break;
                    }
                    if(temp>0 && temp<low_LTP)
                    {
                        state=1;
                        break;
                    }
                    else if(temp>high_HTP)
                        state=2;
                    break;
                case 1:
                    if(temp<0 || temp>7000)
                    {
                        state = -1;
                        break;
                    }
                    if(temp>low_HTP)
                        state = 0;
                    break;
                case 2:
                      if(temp<0 || temp>7000)
                    {
                        state = -1;
                        break;
                    }
                    if(temp<high_LTP)
                        state=0;
                    break;
                default:
                    if(temp<0 || temp>7000)
                    {
                        state = -1;
                        break;
                    }
                    else if(temp>low_LTP && temp<high_HTP)
                    {
                        state = 0;
                        break;
                    }
                    else if(temp<low_LTP)
                    {
                        state = 1;
                        break;
                    }
                    else if(temp>high_HTP)
                    {
                        state = 2;
                        break;
                    }
                    break;
            }
            if(flag){
            for(i=0;i<4;i++)
            {
                display_ram[i]=array1[i+2];
            }
            display_ram[4] = 17;
            decimal = 1;decimal4 = 0;
            blink_all=0;blink_2=0;blink_4=0;
            switch(state)
            {
                case 0:
                   display_ram[5] = 12;
                    LATCbits.LATC5 = 0;
                    break;
                case 1:
                    display_ram[5] = 19;
                    alarm(temp_check);
                    break;
                case 2:
                    display_ram[5] = 18;
                    alarm(temp_check);
                    break;
                default:
                    if(temp>7000)
                    {
                        for(i=0;i<5;i++)
                            display_ram[i] = SHORT[i];
                        display_ram[i] = 16;
                    }
                    else if(temp < 0)
                    {
                        for(i=0;i<6;i++)
                            display_ram[i] = opened[i];
                    }
                    else
                    {
                        for(i=0;i<6;i++)
                            display_ram[i] = rtn[i];
                    }
                    decimal = 0;decimal4 = 0;
                    blink_all=0;blink_2=0;blink_4=0;
                    LATCbits.LATC5 ^= 1;
                    break;
            }
            }
            p_state = state;
            }
           
        
           control_panel();
           LATCbits.LATC6 = 1;
           if(blink_all)
           {
               switch(blink_control_all)
               {
                   case 0:
                       for(i=0;i<6;i++)
                       {
                           display_ram2[i]=display_ram[i];
                           display_ram[i]=27;  
                       }
                       blink_control_all ^= 1;
                       break;
                   case 1:
                       for(i=0;i<6;i++)
                       {
                           display_ram[i] = display_ram2[i];
                           display_ram2[i]=0;
                       }
                       blink_control_all ^= 1;
                       break;
               }
           }
           else if(blink_2)
           {
               switch(blink_control_2)
               {
                   case 0:
                       display_ram3[0]=display_ram[0];
                       display_ram3[1]=display_ram[1];
                       display_ram[0]=27;
                       display_ram[1]=27;
                       blink_control_2 = 1;
                       break;
                   case 1:
                       display_ram[0]=display_ram3[0];
                       display_ram[1]=display_ram3[1];
                       blink_control_2 = 0;
                       break;
               }
                       
           }
           else if(blink_4)
           {
               switch(blink_control_4)
               {
                   case 0:
                       for(i=2;i<6;i++)
                       {
                           display_ram4[i]=display_ram[i];
                           display_ram[i]=27;
                       }
                       blink_control_4 ^= 1;
                       break;
                   case 1:
                       for(i=2;i<6;i++)
                       {
                           display_ram[i]=display_ram4[i];
                          // display_ram4[i]=0;
                       }
                       blink_control_4 ^= 1;
                       break;
               }
           }
           else
           {}
           LATCbits.LATC6 = 0;
            LATCbits.LATC0 = 0;
        }
         
        /*if(PORTAbits.RA3 == 0 || menu)
        {
            delay(100);
            if(PORTAbits.RA3 == 0)
            {
                flag = 0;
                menu = 1;
                if(press_A3)
                    panel_state++;
                press_A3 = 0;
                if(panel_state==0)
                {
                    for(i=0;i<6;i++)
                        display_ram[i] = seg_data[i];
                    decimal = 0;decimal4 = 0;
                }
                else if(panel_state == 1)
                {
                    display_ram[0] = 18;
                    display_ram[1] = 18;
                 //   division(high_HTP);
                 //   for(i=2;i<6;i++)
                 //       display_ram[i] = array1[i];
                 //   decimal = 0;
                }
                else if(panel_state == 2)
                {
                    display_ram[0] = 18;
                    display_ram[1] = 19;
                  //  division(high_LTP);
                  //  for(i=2;i<6;i++)
                   //     display_ram[i] = array1[i];
                  //  decimal = 0;
                }
                
                else if(panel_state == 3)
                {
                    display_ram[0] = 19;
                    display_ram[1] = 18;
                  //  division(low_HTP);
                  //  for(i=2;i<6;i++)
                  //      display_ram[i] = array1[i];
                  //  decimal = 0;
                }
                
                else if(panel_state == 4)
                {
                    display_ram[0] = 19;
                    display_ram[1] = 19;
                  //  division(low_LTP);
                  //  for(i=2;i<6;i++)
                  //      display_ram[i] = array1[i];
                  //  decimal = 0;
                }
                
                
            }
            else
                press_A3 = 1;
            if(!PORTAbits.RA5)
            {
                delay(100);
                if(!PORTAbits.RA5)
                {
                    
                    if(press_up)
                        switch(panel_state)
                        {
                            case 1:
                                display_ram[0] = 18;
                                display_ram[1] = 18;
                                division(high_HTP);
                                for(i=2;i<6;i++)
                                    display_ram[i] = array1[i];
                                decimal = 0;decimal4 = 1;
                                high_HTP++;
                                break;
                            case 2:
                                display_ram[0] = 18;
                                display_ram[1] = 19;
                                division(high_LTP);
                                for(i=2;i<6;i++)
                                    display_ram[i] = array1[i];
                                decimal = 0;decimal4 = 1;
                                high_LTP++;
                                break;
                            case 3:
                                display_ram[0] = 19;
                                display_ram[1] = 18;
                                division(low_HTP);
                                for(i=2;i<6;i++)
                                    display_ram[i] = array1[i];
                                decimal = 0;decimal4 = 1;
                                low_HTP++;
                                break;
                            case 4:
                                display_ram[0] = 19;
                                display_ram[1] = 19;
                                division(low_LTP);
                                for(i=2;i<6;i++)
                                    display_ram[i] = array1[i];
                                decimal = 0;
                                decimal4 = 1;
                                low_LTP++;
                                break;
                                
                        }
                    press_up = 0;
                }
            }
            else
                press_up = 1;
            
            if(PORTAbits.RA4 == 0)
            {    delay(100);
                if(PORTAbits.RA4 == 0)
                {
                    flag = 1;
                    menu = 0;
                    panel_state = 0;
                    for(i=0;i<6;i++)
                    display_ram[i] = rtn[i];
                    decimal4 = 0; decimal = 0;
                    delay(100);
                }
            }
            
        }*/
        
    }
}


void interrupt ISR(void)
{
    unsigned long tmp;
    static char index=0;
    static long refresh = 0;
    static long one_sec=0,twomsec=0;
    if(PIR1bits.TMR2IF)
    {
        refresh++;
        if(refresh > 2)
        {
            refresh=0;
            LATBbits.LATB = 0x00;
         //   if(blink_control)
         //   {
                LATDbits.LATD = digits[display_ram[index]];
         /*       blink_control^= 1;
         //   }
            else if(!blink_control)
            {
                if(blink_all)
                {
                    if(index<6)
                        LATDbits.LATD=0xFF;
                }
                else if(blink_2)
                {
                    if(index<2)
                        LATDbits.LATD=0xFF;
                }
                else if(blink_4)
                {
                    if(index>1 && index<6)
                        LATDbits.LATD=0xFF;
                }
                blink_control ^= 1;
            }*/
            if(index==1 && decimal)
                LATDbits.LATD &= 0x7F;
            if(index==3 && decimal4)
                LATDbits.LATD &= 0x7F;
            LATBbits.LATB = seg_select[index];
            index++;
            if(index > 5)
            {
                index=0;
            }
            else
            {
                asm("NOP");
            }
        }
        else
        {
            _delay(56);

        }
        one_sec++;
        if(one_sec == 400)
        {
            LATCbits.LATC0 = 1;
            one_sec = 0;
        }
        PIR1bits.TMR2IF = 0;
    }
    
    
    if(PIR1bits.ADIF)
    {
        ADCON0bits.ADON = 0;
        //abd++;
        SUM += ADRESLbits.ADRESL;
        tmp = ADRESHbits.ADRESH;
        tmp = tmp << 8;
        SUM += tmp;
        LATCbits.LATC1 ^= 1;
        ADCON0bits.CHS = 2;
        PIR1bits.ADIF = 0;
        ADCON0bits.ADON = 1;
        delay(20);
        ADCON0bits.GO = 1;
    }
    else
    {
        _delay(8059);
    }
}

int division(unsigned long x)
{
	int i;
	unsigned long y = 100000;
	for(i=0;i<5;i++)
	{
		array1[i] = x/y;
		x = x%y;
		y = y/10;
	}
	array1[5] = x;
	return 27;
}

void delay(long x)
{
    int i;
    for(i=0;i<x;i++)
    {}
}

void alarm(long x)
{
    static int count=0;
    int y,z;
    y = (high_LTP/100);
    z = (low_HTP/100)-5;
    if(x>(y+5))
        x=30;
    if(x<z)
        x = 15;
    switch(alarm_state)
    {
        case 0:
            if(x>20)
                off_count = high_alarm_off[x-y];
            else
                off_count = low_alarm_off[x-z];
            alarm_state = 1;
            LATCbits.LATC5 = 0;
            count = 0;
            break;
        case 1:
            if(count == 0) 
            {
                LATCbits.LATC5 = 1;
            }
            if(count == 1)
            {
                LATCbits.LATC5 = 0;
            }
            if(count>1)
            {
                LATCbits.LATC5 = 0;
            }
            count++;
            if(count == off_count)
                alarm_state = 0;
             
            
            break;
    }
}
