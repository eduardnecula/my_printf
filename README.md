

																					~Tema *1* Iocla~ 

Cod scris de: Necula Eduard Ionut 322 CA


	Implementari:

1) int iocla_printf(const char *format, ...)

	Functionalitati:
		a) Functia iocla_printf() primeste formatul de la utilizator:
			%d -> intreg
			%x -> intreg hexazecimal
			%u -> intreg fara semn
			%c -> char
			%s ->string (sir de caractere)
			%% -> afisez %
			/t ->tab
			/n ->next line
		b) Pentru fiecare format in parte functia afiseaza la ecran valoarea corespunzatoare citita din iocla_printf
			ex: iocla_printf("%d", 5) // afisez 5, care este intreg in baza 10
							   ^   ^
							   |   |-----5 trebuie afisat la ecran, in functie de format
							   |_______formatul

			ex: iocla_printf("%c", 66) // afisez B, 66 este cod ASCII pt B
							   ^   ^
							   |   |-----66 trebuie afisat la ecran, in functie de format
						   	   |_______formatul

		c)functia iocla_printf returneaza numarul de caractere afisate la ecran
			ex: int c = iocla_printf("ccc"); //c = 3


2) char *schimbareBaza(int baza_de_numaratie, unsigned int num_de_convertit) 

	Functia schimbareBaza transforma un num_de_convertit intr-o baza_de_numaratie si returneaza un sir de caractere cu numarul schimbat in baza dorita.

		ex: char *sir = schimbare(20, 10); //transform numarul 20 in baza 10, rezultatul final fiind 20

3) static int write_stdout(const char *token, int length) //functie data in schelet
	Functie de afisare a caracterele la stdout, functia returneaza numarul de caractere afisate la stdout.


Explicare cod:

	1. Se citeste caracter cu caracter din format-ul primit de la utilizator, formatul initializat cu va_start. (va_start(arg, format);)
	2. Orice caracter care nu este %, este afisat la ecran si numarat intr-o variabila number_of_ch. Number_of_ch va fi intors ca return daca este mai mare ca 0, altfel se returneaza -1.
	3. Daca se ajunge la caracterul %, urmatorul caracter citit duce intr-un switch, care verifica ce fel de caracter se citeste mai departe: d, c, s, u, x, %.

		3.1. Pentru tipul "d", se face conversia in baza 10 a intregului, in functie daca este pozitiv sau negativ. Dupa conversie, se afiseaza cu functia write_stdout, si se incrementeaza number_of_ch.
		3.2  Pentru tipul "c", se face conversia la char. Dupa conversie, se afiseaza cu functia write_stdout, si se incrementeaza number_of_ch cu 1.
		3.3  Pentru tipul "s", se afiseaza sirul cu write_stdout, si se incrementeaza number_of_ch cu lungimea sirului.
		3.4	 Pentru tipul "u", se face conversia la unsigned int in baza 10, se afiseaza cu write_stdout, si se incrementeaza number_of_ch.
		3.5  Pentru tipul "x", se face conversia la intreg hexazecimal in baza 16, se afiseaza cu write_stdout, si se incrementeaza number_of_ch.
		3.6  Pentru %% se afiseaza % cu write_stdout, si se incrementeaza number_of_ch.

	4. Functia are grija sa nu interfereze cu '\n'. Daca se ajunge la caracterul '\n', se trece pe urmatoarea linie, apoi codul continua.
	5. Functia are grija sa nu interfereze cu '\t'. Daca se ajunge la caracterul '\t', se afiseaza un tab, apoi codul continua. Se incrementeaza number_of_ch;
	6. Dupa ce se citeste un format (ex: "%d"), cu ajutorul lui va_arg, se citeste din iocla_printf, urmatorul int. Int-ul se prelucreaza apoi se afiseaza la ecran. (vezi 3.1 - 3.6)
	7. Programul se opreste cand se ajunge la terminatorul de sir '/0'.