/**
 * @file   	%<%NAME%>%.%<%EXTENSION%>%
 * @author 	%<%USER%>%
 * @version
 * @date 	%<%DATE%>%, %<%TIME%>%
 * @brief
 */


/*#### |Begin| --> Секция - "Include" ########################################*/
#include "../inc/Init_func.h"
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Глобальные переменные" ##########################*/
/*#### |End  | <-- Секция - "Глобальные переменные" ##########################*/


/*#### |Begin| --> Секция - "Локальные переменные" ###########################*/
/*#### |End  | <-- Секция - "Локальные переменные" ###########################*/


/*#### |Begin| --> Секция - "Прототипы локальных функций" ####################*/
/*#### |End  | <-- Секция - "Прототипы локальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание глобальных функций" ####################*/

/**
 * @brief	Функция выполняет инициализации тактового генератора микроконтроллера
 * @return	None
 */
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
Init_TMR2 (void)
{
	T2CONbits.TOUTPS = 0b1001;
	T2CONbits.T2CKPS = 0b00;
	T2CONbits.TMR2ON = 1;
	PIE1bits.TMR2IE = 1;
	PIR1bits.TMR2IF = 0;
	PR2 = 100;

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

void
Init_ADC(void)
{
	ADCON0bits.ADCS = 0b11;
	ADCON0bits.CHS = 0b0000;
	ADCON1bits.ADFM = 0;
	ADCON1bits.VCFG1 = 0;
	ADCON1bits.VCFG0 = 0;
	ADCON0bits.ADON = 1;

	INTCONbits.PEIE = 1;
	
	PIE1bits.ADIE = 1;
	PIR1bits.ADIF = 0;

}
/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
