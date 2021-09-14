#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_length  100 


int print_Line(char *input_Line, int length, unsigned char output_Line[]); // function convert string ":100000" to array 10 00 00, format intelhex
// input_Line is line in hex file :1000...
// length is is input_Line's length
// output_Line 10 00...
int check_Line(unsigned char *line, int length); //function check format intel hex
// line is line, i want to check
// length is line's length
int get_Char(char c); //funtion conver char '3' to int 3 

unsigned char output[max_length], output_length;
unsigned char last_Line[max_length], last_Line_length; // The last line of file and its length



