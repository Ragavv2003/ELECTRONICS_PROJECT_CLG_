 //RFID BASED AUTOMATIC BUS FARE SYSTEM USING 89C51 MICROCONTROLLER


#include<reg51.h>
#include<string.h>
#include<stdio.h>
#define LCDPORT P1
sbit rs=P1^0;
sbit rw=P1^1;
sbit en=P1^2;
sbit Stop1=P2^3;
sbit Stop2=P2^4;
sbit Stop3=P2^5;
sbit Speaker=P2^6;
sbit In1=P0^2;
sbit In2=P0^1;
char i,rx_data[50];
char rfid[13],ch=0;
//char j,Stop[5];                                        //my cmd
int counter1, counter2, counter3;
unsigned char result[1];
 void delay(int itime)
{
    int i,j;
    for(i=0;i<itime;i++)
    for(j=0;j<1275;j++);
}
void daten()
{
rs=1;
rw=0;
    en=1;
delay(5);
    en=0;
}void lcddata(unsigned char ch)
{
    LCDPORT=ch& 0xf0;
daten();
    LCDPORT=(ch<<4) & 0xf0;
daten();
}
void cmden(void)
{
rs=0;
    en=1;
delay(5);
    en=0;
}
void lcdcmd(unsigned char ch)
{
    LCDPORT=ch& 0xf0;
cmden();
    LCDPORT=(ch<<4) & 0xf0;
cmden();
}
void lcdstring(char *str)
{
    while(*str)
    {
lcddata(*str);
        str++;
    }
}
void lcd_init(void)
{
lcdcmd(0x02);
lcdcmd(0x28);
lcdcmd(0x0e);
lcdcmd(0x01);
}
void uart_init()
{
 TMOD=0x20;
 SCON=0x50;
 TH1=0xfd;
 TR1=1;
}
char rxdata()
{
  while(!RI);
   ch=SBUF;    
   RI=0;
    return ch;
}
//main function
void main()
{
Speaker=1;
uart_init();
lcd_init();
	
/*lcdstring("--DOOR IS OPEN--");   
			In1=1;
			In2=0;
			delay(300);
			In1=0;
			In2=0;
			delay(300);
lcdcmd(0x01);
lcdstring("-DOOR IS CLOSE-");
	    In1=0;
	    In2=1;
	    delay(300);
	    In1=1;
	    In2=1;
	    delay(300);*/
	
lcdcmd(0x01);
delay(5);	
lcd_init();
lcdstring("---RFID BASED---");
lcdcmd(0xc0);
delay(5);
lcdstring("BUS TICKETSYSTEM"); 
delay(5);
lcd_init();
lcdstring("---PASSENGER----");
lcdcmd(0xc0);
lcdstring("ENJOY TRAVEL"); 
delay(5);
	
	
	
	//while loop create	
while(1)
    {
		{
		lcd_init();
	
lcdstring("--DOOR IS OPEN--");   
			In1=1;
			In2=0;
			delay(300);
			In1=0;
			In2=0;
			delay(300);
lcdcmd(0x01);
lcdstring("-DOOR IS CLOSE-");
	    In1=0;
	    In2=1;
	    delay(300);
	    In1=1;
	    In2=1;
	    delay(300);
		}
lcdcmd(1);
lcdstring("SCAN YOUR CARD:");
lcdcmd(0xc0);
i=0;
        for(i=0;i<10;i++)
rfid[i]=rxdata();
rfid[i]='\r';
lcdcmd(1);
lcdstring("RFID No. is:");
lcdcmd(0xc0);
        for(i=0;i<10;i++)
lcddata(rfid[i]);
delay(500);	//first ID card dat if statement	
        if(strncmp(rfid,"078$001824_",10)==0)
        {
counter1++;
lcdcmd(1);             
lcdstring("M.S.KAMALESH");
delay(200);
lcdcmd(1);
lcdstring(" BUS FARE ");
delay(200);
lcdcmd(1);
lcdstring("SELECT STOP");
delay(300);
lcdcmd(0xc0);
lcdstring("STP1 STP2 STP3");		
delay(500);	//delay changed 100-500 
lcdcmd(1);					
         if(Stop1==0)     //else   0-1
	{
		lcdcmd(0x0c);
	  lcdstring("STP 1 SELECTED");
		delay(200);
		lcdcmd(1);
		lcdstring("STOP1=10RS");
		delay(100);		
		lcdcmd(0xc0);
		lcdstring("THANK YOU");
		delay(100);
		
	}
		else if(Stop2==0)
		{
			lcdcmd(0x0c);
	    lcdstring("STP 2 SELECTED");
		  delay(200);
			lcdcmd(1);
			lcdstring("STOP2=20RS");
			delay(100);
			lcdcmd(0xc0);
			lcdstring("THANK YOU");
			delay(100);
		}
			else if(Stop3==0)
			{
				lcdcmd(0x0c);
	      lcdstring("STP 3 SELECTED");
		    delay(200);	
				lcdcmd(1);
				lcdstring("STOP3=30RS");
				delay(100);
				lcdcmd(0xc0);
				lcdstring("THANK YOU");
				delay(100);
				
			}
				else
				{
					lcdstring("STP NOT SELECTED");
					delay(250);
				}
			}	
// 2 ID if statement
	 else if(strncmp(rfid,"5$00107595_",10)==0)
        {
counter2++;
lcdcmd(1);             
lcdstring("P.N.RAGAVENDRAN");
delay(200);
lcdcmd(1);
lcdstring(" BUS FARE ");
delay(200);
lcdcmd(1);
lcdstring("SELECT STOP");
delay(300);
lcdcmd(0xc0);
lcdstring("STP1 STP2 STP3");		
 delay(500);	//delay changed 100-500				
lcdcmd(1);					
	if(Stop1==0)
	{
		lcdcmd(1);
		lcdstring("STP 1 SELECTED");
		delay(80);

		lcdcmd(1);
		lcdstring("STOP1=10RS");
		delay(250);
		
		lcdcmd(0xc0);
		lcdstring("THANK YOU");
		delay(100);

	}
		else if(Stop2==0)
		{
		lcdcmd(1);
		lcdstring("STP 2 SELECTED");
		delay(80);

		lcdcmd(1);			
		lcdstring("STOP2=20RS");
		delay(250);
		
		lcdcmd(0xc0);
		lcdstring("THANK YOU");
		delay(100);
		}
		
			else if(Stop3==0)
			{
				lcdcmd(1);
		    lcdstring("STP 3 SELECTED");
		    delay(80);

				lcdcmd(1);				
				lcdstring("STOP3=30RS");
				delay(250);

				lcdcmd(0xc0);
				lcdstring("THANK YOU");
				delay(100);
			}
			
				else
				{
					lcdstring("NOT VALIED");
					delay(250);
	}	}				
	//3 ID if statement
		else if(strncmp(rfid,"3$00107320_",10)==0)
        {
counter1++;
lcdcmd(1);             
lcdstring("RAMAN");
delay(200);
lcdcmd(1);
lcdstring(" BUS FARE ");
delay(200);
lcdcmd(1);
lcdstring("SELECT STOP");
delay(300);
lcdcmd(0xc0);
lcdstring("STP1 STP2 STP3");		
delay(100);		
lcdcmd(1);					
   if(Stop1==0)
	 {
		lcdcmd(0x0c);
	  lcdstring("STP 1 SELECTED");
		delay(200);
		lcdcmd(1);
		lcdstring("STOP1=10RS");
		delay(100);		
		lcdcmd(0xc0);
		lcdstring("THANK YOU");
		delay(100);
		
	}
		else if(Stop2==0)
		{
			
			lcdcmd(0x0c);
	    lcdstring("STP 2 SELECTED");
		  delay(200);
			
			lcdcmd(1);
			lcdstring("STOP2=20RS");
			delay(100);
			
			lcdcmd(0xc0);
			lcdstring("THANK YOU");
			delay(100);
		}
			else if(Stop3==0)
			{
				lcdcmd(0x0c);
	      lcdstring("STP 3 SELECTED");
		    delay(200);
				
				lcdcmd(1);
				lcdstring("STOP3=30RS");
				delay(100);
					
				lcdcmd(0xc0);
				lcdstring("THANK YOU");
				delay(100);
			}		
		}			
		
else					
        {
lcdcmd(1);
lcdstring("CARD DON'T EXIST");
lcdcmd(0xc0);
lcdstring("TRY ANOTHER CARD");
				} 
				
		}
	}

