#include "checkFile.h"

int count_Line = 0;

unsigned char add1 = 0; //bit 31->24
unsigned char add2 = 0; //bit 23->16

char input[max_length];

int main(){

   	char command[30];
  	gets(command);
    
    char *file_Name = (char*) malloc(sizeof(char) * (strlen(command) - 12));
    int index_file_Name;
    // get file .hex in string HexDisplay<file.hex>
    for(index_file_Name = 0; index_file_Name < strlen(command)-12; index_file_Name++){
		file_Name[index_file_Name] = command[index_file_Name + 11];
	}
	
	FILE *fptr;
    fptr = fopen(file_Name,"r");


	if(fptr == NULL){
      	printf("%s could not be opened.", file_Name);   
      	return 0;             
   }
	else{
		printf("\nDo you want to print or save to file .txt");
		char choice[1];
		printf("\nPress 0 to print, 1 to save to file .txt");
		printf("\nYour choice: ");
		gets(choice);
		if(choice[0] == '0' || choice[0] == '\0'){
			printf("\nPrint %s\n", file_Name);
			while(fgets(input, max_length, fptr) != NULL){
				
		    	count_Line+=1; // get number of lines in file
		    	output_length =  print_Line(input, strlen(input), output);
		    	last_Line_length =  print_Line(input, strlen(input), last_Line);
				if(output[3] == 4){  // if record type = 04, it contains 16-31 bit program's address
					add1 = output[4]; // output[4]: bit 31->24 
					add2 = output[5]; // output[5]: bit 23->16 
//					printf("%02x", add1);
//					printf("%02x", add2);
					continue;
				}
				if(output[3] == 1 || output[3] == 5){
					continue;
				}
				printf("%02x", add1); 
				printf("%02x", add2);
				printf("%02x",  output[1]); //bit 15->8 
				printf("%02x ", output[2]); //bit 7->0
				
				
				int i;
				if(output[0] == 16){
					for(i = 0; i < 16; i++){
						printf("%02x ", output[i+4]);//print data
					}
			
					for(i = 0; i < 16; i++){
						if(output[i+4] <= 31){
							printf(".");//print dump
						}
						else{
							printf("%c", output[i+4]);//print dump
						}
						
					}
				}
				else{
					for(i = 0; i < output[0]; i++){
						printf("%02x ", output[i + 4]);//print data
					}
					for(i = output[0]; i < 16; i++){ //print ff if no data
						printf("%02x ", 255);
					}
					for(i = 0; i < output[0]; i++){
						if(output[i + 4] <= 31){
							printf("."); // print dump
						}
						else{
							printf("%c", output[i+4]); // print dump
						}
						
					}
					for(i = output[0]; i < 16; i++){
						printf("%c", 255); // print dump if no data
					}
				}

				if(count_Line == 25){
					printf("\nDo you want to continue printing?\n");
					printf("Press 1 to continue, 0 to exit: ");
					int a;
					scanf("%d", &a);
					if(a == 0){
						exit(0);
					}
					if(a == 1){
						continue;
					}
				}
				
				int check = check_Line(output, output_length);

				if(check == 2){
				  	printf("\nEnd of file.");
				  	
				}
			    if(check == 3){
			      	printf("\nERROR check sum line %d\n", count_Line);
			      	exit(0);
			      	
				}
			}
			if(count_Line == 0){
				printf("\nERROR: wrong format intel hex.");
				exit(0);
			}
			
			int check1 = check_Line(last_Line, last_Line_length);	// check the record type of the last line 		
	  		if(last_Line[3] == 1){
				printf("\n\nEnd of file");							// record type of last line is 01 
			 }	
			else{
				printf("\n\nWrong format intel hex.");
			} 
			printf("\nFile %s has %d lines.", file_Name, count_Line);
	  	}

		if(choice[0] == '1'){
			char user_File[30];
			printf("\nEnter name of your file: ");
			gets(user_File);
			FILE *fp;
			fp = fopen(strcat(user_File, ".txt"),"w+");
			printf("\nSaving to %s...", user_File);
			while(fgets(input, max_length, fptr) != NULL){
				count_Line+=1;
				output_length =  print_Line(input, strlen(input), output);
				
				if(output[3] == 4){  // if record type = 04, it contains 16-31 bit program's address
					add1 = output[4]; // output[4]: bit 31->24 
					add2 = output[5]; // output[5]: bit 23->16 
//					printf("%02x", add1);
//					printf("%02x", add2);
					continue;
				}
				if(output[3] == 1 || output[3] == 5){
					continue;
				}
				fprintf(fp, "\n%02x", add1); 
				fprintf(fp, "%02x",   add2);
				fprintf(fp, "%02x",  output[1]);
				fprintf(fp, "%02x ", output[2]);

				int i;
				if(output[0] == 16){
					for(i = 0; i < 16; i++){
						fprintf(fp, "%02x ", output[i+4]);//print data
					}
			
					for(i = 0; i < 16; i++){
						if(output[i+4] <= 31){
							fprintf(fp,"%c",'.');//print dump
						}
						else{
							fprintf(fp, "%c", output[i+4]);//print dump
						}
						
					}
				}
				else{
					for(i = 0; i < output[0]; i++){
						fprintf(fp, "%02x ", output[i + 4]);//print data
					}
					for(i = output[0]; i < 16; i++){ //print ff if no data
						fprintf(fp, "%02x ", 255);
					}
					for(i = 0; i < output[0]; i++){
						if(output[i + 4] <= 31){
							fprintf(fp,"%c",'.'); // print dump
						}
						else{
							fprintf(fp, "%c", output[i+4]); // print dump
						}
					}
					for(i = output[0]; i < 16; i++){
						fprintf(fp, "%c", ' '); // print dump if no data
					}
				}
				fprintf(fp,"\n");
			}
			if(count_Line == 0){
			   printf("\nERROR: wrong format intel hex.");
			   exit(0);
			}
			printf("\nSaved to %s.", user_File);
			fclose(fp);
		}

	}
	fclose(fptr);
	
	return 0;

}