/// SET CORRECT CODE - PD7
/// WE WANT TO ENTER A CODE - PD0
/// CHECK ENTERED CODE - PD1
/// RESET CORRECT CODE IF IT IS OPEN - PD2

#define F_CPU 8000000UL
#include <xc.h>
#include <util/delay.h>
#include <string.h>

int digit = 1, nr_buton = -1;
int stare = 0;
char cod_corect[5] = "";
char cod_introdus[5] = "";

void reset_display_lines()
{
	PORTA &= 0b11110000;
	PORTC &= 0b00000000;
}

void display(char p, char c)
{
	reset_display_lines();
	switch (c)
	{
		case 0:   PORTC |= 0b00111111; break;
		case 1:   PORTC |= 0b00000110; break;
		case 2:   PORTC |= 0b01011011; break;
		case 3:   PORTC |= 0b01001111; break;
		case 4:   PORTC |= 0b01100110; break;
		case 5:   PORTC |= 0b01101101; break;
		case 6:   PORTC |= 0b01111101; break;
		case 7:   PORTC |= 0b00000111; break;
		case 8:   PORTC |= 0b01111111; break;
		case 9:   PORTC |= 0b01100111; break;
		case 'O': PORTC |= 0b00111111; break;
		case 'P': PORTC |= 0b01110011; break;
		case 'E': PORTC |= 0b01111001; break;
		case 'N': PORTC |= 0b00110111; break;
		case 'S': PORTC |= 0b01101101; break;
		case 'T': PORTC |= 0b01111000; break;
	}
	switch (p)
	{
		case 1: PORTA |= 0b00000001; break;
		case 2: PORTA |= 0b00000010; break;
		case 3: PORTA |= 0b00000100; break;
		case 4: PORTA |= 0b00001000; break;
	}
}

int buttonPressed() /// checks if any button on PORTB is pressed
{
	for (int i = 0; i < 8; i++)
	{
		if (PINB & (1 << i))
		{
			if (stare == 0)
			{
				stare = 1;
				_delay_ms(300);
				return i;
			}
		}
		else
		stare = 0;
	}
	return -1;
}

void afisare_cod_introdus() /// display entered code on 7-segment
{
	for (int i = 0; i < digit - 1; i++)
	{
		int cifra = cod_introdus[i] - '0';
		display(i + 1, cifra);
		_delay_ms(2);
	}
	reset_display_lines();
}

void modificare_cod_introdus() /// modify entered code after button press
{
	cod_introdus[digit - 1] = '0' + nr_buton;
	cod_introdus[digit] = '\0';
	digit++;
}

void verificare_cod() /// check if entered code is correct
{
	if( PIND & (1<<1) ) /// IF CHECK CODE BUTTON PD1 IS PRESSED
	{
		if (strcmp(cod_introdus, cod_corect) == 0) // Correct code
		{
			while (!(PIND & (1 << 0))) /// WAIT FOR PD0 PRESS TO ENTER NEW CODE
			{
				display(1, 'O');
				display(2, 'P');
				display(3, 'E');
				display(4, 'N');
				if (PIND & (1 << 2)) /// PRESS PD2 IF WE WANT TO MODIFY CORRECT CODE
				{
					strcpy(cod_corect, ""); // Reset correct code
					break;
				}
			}

		}
		else // Incorrect code
		{
			while (!(PIND & (1 << 0))) /// WAIT FOR PD0 PRESS TO ENTER NEW CODE
			{
				display(2, 'N');
				display(3, 'O');
			}
			
		}
		reset_display_lines();    // Reset display
		strcpy(cod_introdus, ""); // Reset entered code
		digit = 1;               // Reset digit
	}
}

int main(void)
{
	DDRA |= 0b00001111; // Configure pins for digits
	DDRC |= 0b11111111; // Configure pins for segments
	DDRB &= 0b00000000; // Configure pins for buttons (input)
	DDRD &= ~(1 << 0);  // Configure PD0 as input for code entry
	DDRD &= ~(1 << 1);  // Configure PD1 as input for checking OPEN
	DDRD &= ~(1 << 2);  // Configure PD2 as input for resetting code
	DDRD &= ~(1 << 7);  // Configure PD7 as input for setting code

	while (1)
	{
		nr_buton = buttonPressed();
		
		if( digit <= 4 )
		{
			if (nr_buton != -1)
			modificare_cod_introdus();
			afisare_cod_introdus();
		}
		else
		{
			afisare_cod_introdus();
			if (strcmp(cod_corect, "") == 0) // Code not set yet
			{
				if (PIND & (1 << 7)) // INITIAL CODE SET
				{
					if (stare == 0)
					{
						stare = 1;
						strcpy(cod_corect, cod_introdus); // Save code
						strcpy(cod_introdus, "");         // Reset entered code
						digit = 1;                         // Reset digit
						while (!(PIND & (1<<0)))
						{
							display(2,'S');
							display(3,'E');
							display(4,'T');
						}
						reset_display_lines();
					}
				}
				else
				stare = 0;
			}
			else // Code is already set
			verificare_cod(); // Verify entered code
		}
		
	}
}