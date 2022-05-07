~ Theme * 1 * Iocla ~

Code written by: Necula Eduard Ionut 322 CA


Implementations:

1) int iocla_printf (const char * format, ...)

Features:
a) The iocla_printf () function receives the format from the user:
% d -> int
% x -> integer hexadecimal
% u -> whole without sign
% c -> char
% s -> string
%% -> display%
/ t -> tab
/ n -> next line
b) For each format, the function displays on the screen the corresponding value read from iocla_printf
ex: iocla_printf ("% d", 5) // display 5, which is integer in base 10
^^
| | ----- 5 should be displayed on the screen, depending on the format
| _______ format

ex: iocla_printf ("% c", 66) // display B, 66 is ASCII code for B
^^
| | ----- 66 should be displayed on the screen, depending on the format
| _______ format

c) the iocla_printf function returns the number of characters displayed on the screen
ex: int c = iocla_printf ("ccc"); // c = 3


2) char * changeBase (int count_base, unsigned int convert_number)

The ChangeBase function converts a converted_name to a count_base and returns a string with the number changed in the desired database.

ex: char * sir = change (20, 10); // transform the number 20 into base 10, the final result being 20

3) static int write_stdout (const char * token, int length) // skeletal data function
Function to display characters in stdout, the function returns the number of characters displayed in stdout.


Code explanation:

1. It reads character by character from the format received from the user, the format initialized with va_start. (va_start (arg, format);)
2. Any character other than% is displayed on the screen and counted in a number_of_ch variable. Number_of_ch will be returned as a return if it is greater than 0, otherwise -1 is returned.
3. If the% character is reached, the next character read leads to a switch, which checks what kind of character is read further: d, c, s, u, x,%.

3.1. For type "d", the base 10 is converted to the integer, depending on whether it is positive or negative. After conversion, it is displayed with the write_stdout function, and number_of_ch is incremented.
3.2 For type "c", the char is converted. After conversion, it is displayed with the write_stdout function, and incremented number_of_ch by 1.
3.3 For type "s", the string with write_stdout is displayed, and the number_of_ch is incremented by the length of the string.
3.4 For type "u", convert to unsigned int in base 10, display with write_stdout, and increment number_of_ch.
3.5 For type "x", convert to the full hexadecimal in base 16, display with write_stdout, and increment number_of_ch.
3.6 For %%% is displayed with write_stdout, and number_of_ch is incremented.

4. The function is careful not to interfere with '\ n'. If the '\ n' character is reached, go to the next line, then the code continues.
5. The function is careful not to interfere with '\ t'. If the '\ t' character is reached, a tab is displayed, then the code continues. Increasing number_of_ch;
6. After reading a format (ex: "% d"), with the help of va_arg, read from iocla_printf, the following int. The int is processed and then displayed on the screen. (see 3.1 - 3.6)
7. The program stops when the string terminator '/ 0' is reached.