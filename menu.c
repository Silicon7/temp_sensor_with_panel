#include "main.h"
static char press_up=1 , panel_state=-1 , press_enter=1, press_down=1,press_esc=1;
char menu=0,flag=1;
static char on_enter=0,off_enter=0,on_up=0,off_up=0,on_dwn=0,off_dwn=0,on_esc=0,off_esc=0;
static char blink_all=0,blink_2,blink_4;
static const char debounce_time=1,debounce_time_off=3;
char blink_control_all=0,blink_control_2=0,blink_control_4=0;
void control_panel(void)
{
    int i;
    if(PORTEbits.RE0 == 0 || menu)
    {
        LATCbits.LATC5=0;
        if(PORTEbits.RE0 == 0)
        {
            on_enter++;
            off_enter=0;
            if(on_enter >= debounce_time){
            flag = 0;
            menu = 1;
            if(press_enter)
                panel_state++;
            panel_state = panel_state%5;
            press_enter = 0;

            if(panel_state == 0)
            {
                for(i=0;i<6;i++)
                    display_ram[i] = adjust[i];
                decimal = 0;decimal4 = 0;blink_all=1;blink_2=0;blink_4=0;blink_control_all=0;
            }
            else if(panel_state == 1)
            {
                display_ram[0] = 18;
                display_ram[1] = 18;
                division(high_HTP);
                for(i=2;i<6;i++)
                    display_ram[i] = array1[i];
                decimal = 0;decimal4 = 1; blink_all=0;blink_2=1;blink_4=0;blink_control_2=0;
            }
            else if(panel_state == 2)
            {
                display_ram[0] = 18;
                display_ram[1] = 19;
                division(high_LTP);
                for(i=2;i<6;i++)
                    display_ram[i] = array1[i];
                decimal = 0;decimal4 = 1; blink_all=0;blink_2=1;blink_4=0;blink_control_2=0;
            }

            else if(panel_state == 3)
            {
                display_ram[0] = 19;
                display_ram[1] = 18;
                division(low_HTP);
                for(i=2;i<6;i++)
                    display_ram[i] = array1[i];
                decimal = 0;decimal4 = 1; blink_all=0;blink_2=1;blink_4=0;blink_control_2=0;
            }

            else if(panel_state == 4)
            {
                display_ram[0] = 19;
                display_ram[1] = 19;
                division(low_LTP);
                for(i=2;i<6;i++)
                    display_ram[i] = array1[i];
                decimal = 0;decimal4 = 1; blink_all=0;blink_2=1;blink_4=0;blink_control_2=0;
            }
            }}
        else
        {
            on_enter=0;
            off_enter++;
            if(off_enter>=debounce_time_off)
            {
                press_enter = 1;
              //  on_enter=0;
            }
        }
        
        
        if(!PORTAbits.RA4)
        {
            off_up=0;
            on_up++;
            if(!PORTAbits.RA4 && on_up>=debounce_time)
            {

                if(press_up)
                    switch(panel_state)
                    {
                        case 1:
                            high_HTP++;
                            display_ram[0] = 18;
                            display_ram[1] = 18;
                            division(high_HTP);
                            for(i=2;i<6;i++)
                                display_ram[i] = array1[i];
                            decimal = 0;decimal4 = 1; blink_all=0;blink_2=0;blink_4=1;blink_control_4=0;
                            break;
                        case 2:
                            high_LTP++;
                            display_ram[0] = 18;
                            display_ram[1] = 19;
                            division(high_LTP);
                            for(i=2;i<6;i++)
                                display_ram[i] = array1[i];
                            decimal = 0;decimal4 = 1; blink_all=0;blink_2=0;blink_4=1;blink_control_4=0;
                            break;
                        case 3:
                            low_HTP++;
                            display_ram[0] = 19;
                            display_ram[1] = 18;
                            division(low_HTP);
                            for(i=2;i<6;i++)
                                display_ram[i] = array1[i];
                            decimal = 0;decimal4 = 1; blink_all=0;blink_2=0;blink_4=1;blink_control_4=0;
                            
                            break;
                        case 4:
                            low_LTP++;
                            display_ram[0] = 19;
                            display_ram[1] = 19;
                            division(low_LTP);
                            for(i=2;i<6;i++)
                                display_ram[i] = array1[i];
                            decimal = 0;
                            decimal4 = 1; blink_all=0;blink_2=0;blink_4=1;blink_control_4=0;
                            
                            break;

                    }
                press_up = 0;
            }
        }
        else
        {
            on_up=0;
            off_up++;
            if(off_up>=debounce_time_off)
                press_up = 1;
        }
        
        
        if(PORTAbits.RA5 == 0)
        {
            on_dwn++;
            off_dwn=0;
            if(PORTAbits.RA5 == 0 && on_dwn>=debounce_time && press_down)
            {
                press_down = 0;
                switch(panel_state)
                {
                    case 1:
                        high_HTP--;
                        display_ram[0] = 18;
                        display_ram[1] = 18;
                        division(high_HTP);
                        for(i=2;i<6;i++)
                            display_ram[i] = array1[i];
                        decimal = 0;decimal4 = 1; blink_all=0;blink_2=0;blink_4=1;blink_control_4=0;
                        
                        break;
                    case 2:
                        high_LTP--;
                        display_ram[0] = 18;
                        display_ram[1] = 19;
                        division(high_LTP);
                        for(i=2;i<6;i++)
                            display_ram[i] = array1[i];
                        decimal = 0;decimal4 = 1; blink_all=0;blink_2=0;blink_4=1;blink_control_4=0;
                        
                        break;
                    case 3:
                        low_HTP--;
                        display_ram[0] = 19;
                        display_ram[1] = 18;
                        division(low_HTP);
                        for(i=2;i<6;i++)
                            display_ram[i] = array1[i];
                        decimal = 0;decimal4 = 1; blink_all=0;blink_2=0;blink_4=1;blink_control_4=0;
                        
                        break;
                    case 4:
                        low_LTP--;
                        display_ram[0] = 19;
                        display_ram[1] = 19;
                        division(low_LTP);
                        for(i=2;i<6;i++)
                            display_ram[i] = array1[i];
                        decimal = 0;
                        decimal4 = 1; blink_all=0;blink_2=0;blink_4=1;blink_control_4=0;
                        
                        break;
                }
            }
        }
        else
        {
            off_dwn++;
            on_dwn=0;
            if(off_dwn>=debounce_time_off)
                press_down = 1;
        }
        
        
        if(PORTAbits.RA3 == 0)
        {    
            on_esc++;
            off_esc=0;
            if(PORTAbits.RA3 == 0 && on_esc>=debounce_time)
        //    if(PORTAbits.RA4 == 0)
            {
                flag = 1;
                menu = 0;
                panel_state = -1;
                for(i=0;i<6;i++)
                display_ram[i] = rtn[i];
                decimal4 = 0; decimal = 0; blink_all=0;blink_2=0;blink_4=0;
            }
        }
        else
        {
            off_esc++;
            on_esc=0;
        }
    }
}