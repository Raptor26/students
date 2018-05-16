/*
 * File:   main.c
 * Author: CHRONOS
 *
 * Created on 4 апреля 2018 г., 16:04
 */

#define _XTAL_FREQ              4000000u
// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
unsigned int led0cont;
void Init_Oscillator(void);
void Init_InOutPorts(void);
void Init_Adc(void);
void Init_UART1(void);

int myVar;

uint16_t adcValue;


void
main(void)
{

	Init_Oscillator();
	Init_InOutPorts();
	Init_Adc();
	Init_UART1();


	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;

	T2CONbits.TOUTPS = 0b1001;
	T2CONbits.T2CKPS = 0b00;
	T2CONbits.TMR2ON = 1;
	PIE1bits.TMR2IE = 1;
	PIR1bits.TMR2IF = 0;
	PR2 = 100;



	while (1)
	{

		if (TXSTAbits.TRMT == 1)
		{
			TXREG = 'H';
		}

		TXREG = 0xFF;

		if (ADCON0bits.GO == 0)
		{
			ADCON0bits.GO = 1;
		}
		//        PORTBbits.RB0 = 1;
		//        __delay_us(1000000);
		//        PORTBbits.RB0 = 0;
		//        __delay_us(1000000);
		if (led0cont >= 1000)
		{
			led0cont = 0;
			if (PORTBbits.RB0 == 0)
			{
				PORTBbits.RB0 = 1;
			}
			else
			{
				PORTBbits.RB0 = 0;
			}
		}
	}
	return;
}


void interrupt
ISR_my(void)
{
	if (PIE1bits.TMR2IE == 1 && PIR1bits.TMR2IF == 1)
	{
		PIR1bits.TMR2IF = 0;
		led0cont++;
	}
	if (PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1)
	{
		PIR1bits.ADIF = 0;
		uint16_t adcValueL = (uint16_t) ADRESL;
		adcValueL = (adcValueL >> 6) & 0x0003;

		uint16_t adcValueH = (uint16_t) ADRESH;
		adcValueH = (adcValueH << 2) & 0x03FC;

		adcValue = adcValueL | adcValueH;
	}
}


void
Init_Oscillator(void)
{
	OSCCON = 0b01100111;
	OSCCONbits.IRCF = 0b110;
	OSCCONbits.OSTS = 0;
	OSCCONbits.HTS = 1;
	OSCCONbits.LTS = 1;
	OSCCONbits.SCS = 1;
}


void
Init_InOutPorts(void)
{
	// отключение аналоговых выводов.
	ANSELH = 0;

	//конфигурирование порта DS1 для светодиода.
	TRISBbits.TRISB0 = 0;
	PORTBbits.RB0 = 1;

	//конфигурация входа для АЦП
	TRISAbits.TRISA0 = 1;
	ANSELbits.ANS0 = 1;

}


void
Init_Adc(void)
{
	ADCON0bits.ADCS = 0b11;
	ADCON0bits.CHS = 0b0000;
	ADCON1bits.ADFM = 0;
	ADCON1bits.VCFG1 = 0;
	ADCON1bits.VCFG0 = 0;
	ADCON0bits.ADON = 1;

	//вклчение прерывания
	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;
	PIE1bits.ADIE = 1;
	PIR1bits.ADIF = 0;

}


void
Init_UART1(void)
{
	TXSTAbits.TXEN = 1;
	TXSTAbits.BRGH = 1;

	RCSTAbits.SPEN = 1;
	RCSTAbits.CREN = 1;
	RCSTAbits.FERR = 1;
	RCSTAbits.OERR = 1;

	BAUDCTLbits.ABDOVF = 1;
	BAUDCTLbits.SCKP = 1;
	BAUDCTLbits.ABDEN = 1;
	BAUDCTLbits.BRG16 = 1;
	SPBRG = 25;
	//отключение аналоговых портов
	ANSELH = 0;

	PORTCbits.RC7 = 1;
	PORTCbits.RC6 = 0;




}
