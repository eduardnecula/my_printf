//NECULA EDUARD-IONUT 322 CA 
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// baze de numaratie
#define BAZA_10 10
#define BAZA_16 16
#define BUFFER_LENGTH 1000
#define BAZA_REPREZENTARE "0123456789abcdefghijklmnopqrstuvwxyz"

static int write_stdout(const char *token, int length)
{
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

char *schimbareBaza(int baza_de_numaratie, unsigned int num_de_convertit) 
{
	if(baza_de_numaratie == 0) {
		return NULL;
	} else {
		static char buffer[BUFFER_LENGTH];
		char *numar_convertit = &buffer[BUFFER_LENGTH - 1];
		*numar_convertit = '\0'; //setez terminatorul de sir
		char bazeDeReprezentare[] = BAZA_REPREZENTARE;//pentru a putea reprezenta in orice baza

		do
		{
			*(--numar_convertit) = bazeDeReprezentare[num_de_convertit % baza_de_numaratie];
			num_de_convertit = num_de_convertit / baza_de_numaratie;
		}while(num_de_convertit != 0);

		return numar_convertit;	
	}
}

int iocla_printf(const char *format, ...)
{
	if(format == NULL) {// in caz ca nu primesc nimic
		return -1;
	}
	// pentru functia infinita
	va_list arg;
	va_start(arg, format);

	const char* nr_schimbat;
	//char *character;
	int number_of_ch = 0;// nr de caractere afisate la ecran
	int integer;// %d
	unsigned int unsigned_int;// %u
	char character;// %c
	unsigned int intreg_hexazecimal;// %x
	char* string;// %s

	while(*(format) != '\0') {//citesc caracter cu caracter
		while(((*format) != '%') && ((*format) != '\0')) {// afisez tot pana la intalnirea "%" sau pana la terminarea caracterelor
			number_of_ch += write_stdout(format, 1);// pentru fiecare caracter afisat cresc
			format++;// trec la urmatorul caracter
		}

		if(*format == '%') {// pentru a trece de la % la d
			format++;// cu acest if ma asigur ca nu trec la urmatorul caracter daca dau de /n
		}

		switch(*format) {
			case 'd' : {
				integer = va_arg(arg, int);// daca ajung la %d iau din functie intregul
				if(integer < 0) {// pentru int negatic schimb semnul
					nr_schimbat = schimbareBaza(BAZA_10, -integer);// convertesc in baza 10
					number_of_ch++;// adun un caracter pentru simbolul -
					write_stdout("-", 1);
					number_of_ch += write_stdout(nr_schimbat, strlen(nr_schimbat));// incrementez nr de caractere afisate si afisez la stdout
				} else {
					char* nr_schimbat = schimbareBaza(BAZA_10, integer);// convertesc in baza 10
					number_of_ch +=	write_stdout(nr_schimbat, strlen(nr_schimbat));// incrementez nr de caractere afisate si afisez la stdout
				}
				format++;// trec la urmatorul caracter
				break;
			}
			case 'u' : {
				unsigned_int = va_arg(arg, unsigned int);// daca ajung la %u, iau din iocla_printf  unsigned int-ul corespunzator
				nr_schimbat = schimbareBaza(BAZA_10, unsigned_int);// convertesc nr in baza 10
				number_of_ch += write_stdout(nr_schimbat, strlen(nr_schimbat));// incrementez nr de caractere afisate si afisez la stdout
				format++;// trec la urmatorul caracter
				break;
			}
			case 'c' : {
				character = (char)va_arg(arg, int);// daca ajung la %c, iau din iocla_printf caracterul
				char* ptr = &character;// obtin adresa caracterului
				number_of_ch += write_stdout(ptr, 1);// incrementez nr de caractere afisate si afisez la stdout
				format++;// trec la urmatorul caracter
				break;
			}
			case 'x' : {
				intreg_hexazecimal = va_arg(arg, unsigned int);// daca ajung la %x, iau din iocla_printf intregul hexazecimal
				nr_schimbat = schimbareBaza(BAZA_16, intreg_hexazecimal);// convertesc in baza 16
				number_of_ch += write_stdout(nr_schimbat, strlen(nr_schimbat));// incrementez nr de caractere afisate si afisez la stdout
				format++;// trec la urmatorul caracter
				break;
			}
			case '%': {
				number_of_ch += write_stdout("%", 1);// daca ajung la %% incrementez nr de caractere si afisez la stdout
				format++;// trec la urmatorul caracter
				break;
			}
			case 's': {
				string = va_arg(arg, char *);// daca ajung la %s, iau din iocla_printf sirul de caractere
				number_of_ch += write_stdout(string, strlen(string));// incrementez nr de caractere afisate si afisez la stdout
				format++;// trec la urmatorul caracter
				break;
			}
		}
	}
	va_end(arg);// pentru sfarsitul functiei infinite

	if(number_of_ch == 0)// daca nu am caractere afisate
		return -1;
	return number_of_ch;// returnare nr de caracatere
}