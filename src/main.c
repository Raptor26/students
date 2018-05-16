/**
 * @file   	%<%NAME%>%.%<%EXTENSION%>%
 * @author 	%<%USER%>%
 * @version
 * @date 	%<%DATE%>%, %<%TIME%>%
 * @brief
 */


/*#### |Begin| --> Секция - "Include" ########################################*/
#include "../inc/configurationBits.h"
#include "../inc/main.h"
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Глобальные переменные" ##########################*/

/* Счетчик для моргания светодиодом*/
uint16_t led0cont;

/* Значение аппаратного регистра АЦП */
uint16_t adcValue;
/*#### |End  | <-- Секция - "Глобальные переменные" ##########################*/


/*#### |Begin| --> Секция - "Локальные переменные" ###########################*/
/*#### |End  | <-- Секция - "Локальные переменные" ###########################*/


/*#### |Begin| --> Секция - "Прототипы локальных функций" ####################*/
/*#### |End  | <-- Секция - "Прототипы локальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание глобальных функций" ####################*/
int main (void)
{
	Init_Oscillator();

	/* Отключение глобального прерывания на время инициализации
	 * микроконтроллера */
	INTCONbits.GIE = 0;

	Init_InOutPorts();
	Init_TMR2();
	Init_UART1();
	Init_ADC();

	/* Разрешение прерывания */
	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;

	while (1)
	{

	}
	return 0;
}

void interrupt
ISR_my(void)
{
	/* Если произошло преррывание от TMR2 */
	if (PIE1bits.TMR2IE == 1 && PIR1bits.TMR2IF == 1)
	{
		PIR1bits.TMR2IF = 0;
		led0cont++;
	}

	/* Если произошло прерывание от АЦП */
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
/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/