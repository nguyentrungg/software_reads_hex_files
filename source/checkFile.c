#include "checkFile.h"

int print_Line(char *input_Line, int length, unsigned char output_Line[])
{
   unsigned char input1, input2;
   unsigned char res;
   unsigned char res1[max_length];
   if (input_Line[0] != ':'){
   		printf("\nERROR: wrong format intel hex");
   		exit(0);
   } 
   else{
	   int index_input   = 1;
	   int index_output  = 0;
	
	   while(index_input < length - 1) {
	      input1 = get_Char(input_Line[index_input++]);
	      input2 = get_Char(input_Line[index_input++]);
	      
	      res = input1<<4 | input2;
	      output_Line[index_output++] = res;
	     //printf("%02x ", res);
	   }
	   
	   printf("\n");
	   
	   return index_output;
	}
}



int get_Char(char c){

    if(c >= '0' && c <= '9'){
        return c - '0';
    }
    if(c >= 'A' && c <= 'F'){
        return c - 'A' + 10;
    } 
	  if(c >= 'a' && c <= 'f'){
        return c - 'a' + 10;
    }
    else{
    	printf("\nWrong char in next line.");
    	exit(0);
	}
}

int check_Line( unsigned char *line, int length)
{
		unsigned char  ll;
		unsigned char  high_Add;
		unsigned char  low_Add;
		unsigned int   address; 
		unsigned char  tt;
		unsigned char  dd[max_length];
		unsigned char  check_Sum;

		ll = line[0]; 
		if (ll == 0){
			// error: no data
			return 1;
		}     

		tt = line[3];
		if (tt == 1){
			// end of file
			return 2;
		}
 
		check_Sum = line[length - 1];
	    unsigned char sum;
	    int k;
	    for(k = 0; k < length - 1; k++){
	         sum += line[k];
	    }
	    if(check_Sum != (unsigned char)(0x01 + ~sum)){
	    	// error: check sum
	        return 3;
	    }	
}
