//--------------------------------------------
// NAME: Ivo Stratev
// CLASS: XIb
// NUMBER: 16
// PROBLEM: #1
// FILE NAME: xxxxxx.yyy.zzz (unix file name)
// FILE PURPOSE:
// Piece implementation of unix command wc:
// 	Count how many lines, words and bytes a given file contents and output the result on standart output.
// 	If no file is given, as output is provided result from coontering how many lines, words and bytes standart input contents.
// 	If the given file is provided as - as output is provided result from coontering how many lines, words and bytes standart input contents.
// In this implementation are used only open(), read(), write() and close(): system functions and no other non-selfmade functions are used, such as: perror().
// Whole output is done only by system calls by write().
// No perror() function is used for writing error massages instead series of function calls are made that only use write() and errno is used to output the correct error massage.
//---------------------------------------------

//--------------------------------------------
// HEADER: <sys/types.h>
// Required by system function: 
//----------------------------------------------
#include <sys/types.h>	
//--------------------------------------------
// HEADER: <sys/types.h>
// Required by system function: 
//----------------------------------------------	
#include <sys/stat.h>	
//--------------------------------------------
// HEADER: <sys/types.h>
// Required by system function: 
//---------------------------------------------- 	
#include <fcntl.h>
//--------------------------------------------
// HEADER: <sys/types.h>
// предназначение на функцията
//----------------------------------------------		
#include <stdio.h>
//--------------------------------------------
// HEADER: <sys/types.h>
// Required by system function: 
//----------------------------------------------		
#include <unistd.h>
//--------------------------------------------
// HEADER: <sys/types.h>
// Required in order to map errors throwed by all functions except main().
//----------------------------------------------		
#include <errno.h>

int words = 0;	//Used for counting words from file or stdin.
int bytes = 0;	//Used for counting bytes from file or stdin.
int lines = 0;	//Used for counting lines from file or stdin.
int total_words = 0;	//Used for counting total words.
int total_bytes = 0;	//Used for counting total bytes.
int total_lines = 0;	//Used for counting total lines.	

//--------------------------------------------
// FUNCTION: get_extention
// Returns lg counter (decimal logarithm of counter caliber)
// PARAMETERS: counter
// counter: Is used to calculate the rigth lg (counter caliber) in order to write counter properly.
//----------------------------------------------
int get_extention(int counter);	
//--------------------------------------------
// FUNCTION: write_counter
// Writes counter value on stdout.
// PARAMETERS: counter
// counter: It's writed on stdout by value.
//----------------------------------------------							
int write_counter(int counter);
//--------------------------------------------
// FUNCTION: get_counters_from_file
// Sets properly the global counters: lines, words and bytes for the given file.
// PARAMETERS: file_pathname
// file_pathname: Is used in order to set properly the global counters: lines, words and bytes for it.
//----------------------------------------------							
int get_counters_from_file(char *file_pathname);
//--------------------------------------------
// FUNCTION: get_counters_from_stdin
// Sets properly the global counters: lines, words and bytes for stdin content.
// PARAMETERS:
// None
//----------------------------------------------					
int get_counters_from_stdin(void);	
//--------------------------------------------
// FUNCTION: write_reference
// Outputs reference value appending it on (excluding '\0') stderr if stream is 1 or on stdout if stream is different from 0.
// PARAMETERS:
// reference, stream.
// reference:
//	Is used to be appened to stream pointed out by stream value.
//stream:
//	Is used to append reference to stream that points to.
//----------------------------------------------						
int write_reference(char *reference, int stream);
//--------------------------------------------
// FUNCTION: write_tab
// Appends tab char ('\t') to stream that stream points out.
// PARAMETERS:
// reference, stream.
// reference:
//	Is used to appened tab char ('\t') to stream pointed out by stream value.
//stream:
//	Is used to append tab char ('\t') to stream that points to.
//----------------------------------------------					
int write_tab(int stream);	
//--------------------------------------------
// FUNCTION: write_newline
// Appends newline char ('\n') to stream that stream points out.
// PARAMETERS:
// reference, stream.
// reference:
//	Is used to appened newline char ('\n') to stream pointed out by stream value.
//stream:
//	Is used to append newline char ('\n') to stream that points to.
//----------------------------------------------								
int write_newline(int stream);	
//--------------------------------------------
// FUNCTION: write_dots
// Appends colon char (':') to stream that stream points out.
// PARAMETERS:
// reference, stream.
// reference:
//	Is used to appened colon char (':') to stream pointed out by stream value.
//stream:
//	Is used to append colon char (':') to stream that points to.
//----------------------------------------------							
int write_dots(int stream);
//--------------------------------------------
// FUNCTION: write_wc
// Appends w and c chars  to stream that stream points out.
// PARAMETERS:
// reference, stream.
// reference:
//	Is used to appened w and c chars to stream pointed out by stream value.
//stream:
//	Is used to append w and c chars to stream that points to.
//----------------------------------------------								
int write_wc(int stream);	
//--------------------------------------------
// FUNCTION: write_total
// Appends t, o, t, a, and l chars  to stream that stream points out.
// PARAMETERS:
// reference, stream.
// reference:
//	Is used to appened t, o, t, a, and l chars to stream pointed out by stream value.
//stream:
//	Is used to append t, o, t, a, and l chars to stream that points to.
//----------------------------------------------									
int write_total(int stream);	
//--------------------------------------------
// FUNCTION: write_total_counters
// Outputs on stdout values of total: lines, words and bytes and the string total(excluding '\0'), all seperated by tab folowed by newline.
// PARAMETERS:
// total_lines, total_words, total_bytes
// All three parameters are used in order to write their values on stdout.
//----------------------------------------------								
void write_total_counters(int total_lines, int total_words, int total_bytes);
//--------------------------------------------
// FUNCTION: wordcounter_file
// Counts and outputs number of lines, words and bytes for the given file on stdout.
// PARAMETERS: file_pathname.
// file_pathname: Is used in order to count and output number of lines, words and bytes for it.
//----------------------------------------------
void wordcounter_file(char *file_pathname);
//--------------------------------------------
// FUNCTION: wordcounter_stdin
// Counts and outputs number of lines, words and bytes for stdin content on stdout.
// PARAMETERS: reference.
// reference: Is used in order to output and append it's value to stdout.
//----------------------------------------------						
void wordcounter_stdin(char *reference);
//--------------------------------------------
// FUNCTION: write_error
// Appends only the error massage to stderr wich error_number points out to.
// PARAMETERS: error_number.
// error_number: Is used to decode wich error massage to append to stderr with it's value.
//----------------------------------------------						
int write_error(int error_number);
//--------------------------------------------
// FUNCTION: write_error_massage
// Appends the complete error massage to stderr wich error_number points out to and where the error ocurred (sometimes this can be only a singel symbol or symbols, because the error ocurred while trying to write them to a given stream).
// PARAMETERS:
// error, reference.
// error:
//	Used in order to write proper error massage (See: write_error()).
// reference:
//	Is used to know where the error ocurred(sometimes this can be only a singel symbol or symbols, because the error ocurred while trying to write them to a given stream)
//----------------------------------------------							
void write_error_massage(int error, char *reference);					

//--------------------------------------------
// FUNCTION: main
// Processed arguments passed on run time (also tells the program from where to start).
// PARAMETERS:
// argc, argv.
// argc"
//	Is taken on run time and retruns the number of arguments passed.
// argv:
//	Is taken on run time and retruns the different arguments and their values, those argument can be path to files, abstract reference to stdin and program name.
//----------------------------------------------
int main(int argc,char **argv)
{
	int i;	//Define counter to iterate among arguments.
	int total_flag = 1;	//Define flag in order to know when and when not to output the total number of counter for total: lines, words and bytes and set it to 1(to output them by default).
	char stdin_name[1] = {'\0'};	//Define and inicializate and empty stdin name to use when only one argument is passed(program name).

	if(argc < 3)	//If argument number is less then 3 set flag to 0 and don't output total.
		total_flag = 0; //If enter inside the upper if set flag to 0.

	if(argc == 1)	//If argument number is 1 (no arguments to processed are passed) output number of lines, words and bytes from stdin.
		wordcounter_stdin(stdin_name);	//IF enter inside the upper if output number of lines, words and bytes from stdin.
		
	for(i = 1;i < argc;i++)	//Loop in order to iterate among arguments wich need to be processed.
	{
		if((argv[i][0] == '-') && (argv[i][1] == '\0'))	//If the argument is abstract reference to stdin ('-') output number of lines, words and bytes from stdin.
			wordcounter_stdin(argv[i]);	//IF enter inside the upper if output number of lines, words and bytes from stdin.
			
		else	//Otherwise treat argument as path to file and processed it.
			wordcounter_file(argv[i]);	//IF enter inside the upper else output number of lines, words and bytes from the given file.		 
	}

	if(total_flag == 1)	//If flag that states do or don't output total counters for lines, words and bytes is 1 do output them.
		write_total_counters(total_lines, total_words, total_bytes);	//IF enter inside the upper if output number of total: lines, words and bytes.
		
	return 0;	//Retrun 0 wich means that program executed succesful and no fatal erros occured.
}

int get_extention(int counter)
{
	int i = 1;	//Define counter in order to get the rigth power of 10.
	while(1)	//Infint loop from wich break only if got the rigth power of 10.
	{
		if((counter / i)  < 1)	//If counter divided by i is less then 1 return i divided by 10.
			return (i / 10);	//IF enter inside the upper if return i divided by 10..

		i = i*10	//Increment i by multiple it with 10.
	}
}

int write_counter(int counter)
{
	int counter_extention = get_extention(counter);	//Define a varible and set it with value retruned by get_extention() in order to be used as counter in futere phase of function execution.
	char digit_to_char[1];	//Define a single empty varible to holde the digit wich will be writen as charecter.
	char reference[] = {'I', 'n', ' ', 'f', 'u', 'n', 'c', 't', 'i', 'o', 'n', ':', ' ', 'w', 'r', 'i', 't', 'e', '_', 'c', 'o', 'u', 'n', 't', 'e', 'r', '\0'};	//Define and inicializate a string in order to be used to state that error occured while executing this function.
	if(counter_extention <= 0)	//if counter value is 0 (counter caliber is less or equal to 0).
	{	//If entered inside upper loop do:
		digit_to_char[0] = 48;	//Temporary hold 0 charecter.
		int status_returned = write(STDOUT_FILENO, digit_to_char, 1);	//Write 0 to stdout.
				if((status_returned != 1) && (errno > 0))	//IF error ocured while writing 0 write proper error massage and retrun 1 (function failed).
				{
					write_error_massage(errno, reference);	//If entered inside upper if send proper error massage and indicate that this function failed.
	
					return 1;	//Indicate that something went wrong.
				}
	}
	else if(counter_extention == 1)	//else if counter caliber is 1 (it's a singel digit) write it to stdout (BELJKA DO MEN PROVERI KAKVO SHTE STANE AKO NQMASH WHILE A SAMO IZVEJDANE) .
	{//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		while(counter > 0)	//while counter is greater than 0 do:
		{
			digit_to_char[0] = (counter % 10) + 48;	//Convert digit from integer to charecter and set this value to digit_to_char to holde it temporary.
			counter = counter / 10;	//Decrement counter by deviding it with 10.
			if(digit_to_char[0] >= 48 && digit_to_char[0] <= 57)	//If value od digit_to_char is a valid number write it to stdout.
			{
				int status_returned = write(STDOUT_FILENO, digit_to_char, 1);	//Write digit_to_cahr value to stdout.
				if((status_returned != 1) && (errno > 0))	//If writing digit_to_char failed send proper error massage and indicate that this function failed by returnig 1.
				{
					write_error_massage(errno, reference);		//Send proper error massage that error ocurred while executing this function.
			
					return 1;	//Indicate that something went wrong while executing this function.
				}
			}
		}
	}
	else	//Otherwise write counter wich caliber is greater than 1.
	{
		while(counter_extention > 0)	//While counter caliber is greater than 0, write single digit to stdout.
		{
			digit_to_char[0] = (counter / counter_extention) + 48;	//Set temporary value to digit_to_char to hold.
			counter = counter % counter_extention;	//Decrement counter by making modular division with counter_extention (caliber value).
			counter_extention = counter_extention / 10;	//Decrement counter_extention (counter value) by diveding it with 10.
			if(digit_to_char[0] >= 48 && digit_to_char[0] <= 57)	//If value od digit_to_char is a valid number write it to stdout.
			{
				int status_returned = write(STDOUT_FILENO, digit_to_char, 1);	//Write digit_to_cahr value to stdout.
				if((status_returned != 1) && (errno > 0))	//If writing digit_to_char failed send proper error massage and indicate that this function failed by returnig 1.
				{
					write_error_massage(errno, reference);	//Send proper error massage that error ocurred while executing this function.

					return 1;	//Indicate that something went wrong while executing this function.
				}
			}
		}
	}

	return 0;	//If no error ocurred while executing this function indicate it by returning 0.
}

int get_counters_from_file(char * file_pathname)
{	
	int file_discriptor = open(file_pathname, O_RDONLY);	//Define and set value to file_discriptor by returning the first free file descriptor (file descriptor is:  a small non negative digit that is returned if system function open() succesfuly executed) from opening the given file with system function open().
	if(file_pathname[0] == '-')	//If file_pathname is starting with '-' that means that it's given as argument in wich case take reaction and set errno to 22 (invalid argument), because in this implementaion arguments aren't provided. 
		errno = 22;	//Set errno properly, because open only sets it to 2 (No such file or directory) and this implemntaion trys to be as close to real wc as possible.
	if((file_pathname[0] == '-') && (file_pathname[1] == '-'))
		errno = 125;
	if((file_discriptor == -1) && (errno > 0))	
	{
		write_error_massage(errno,file_pathname); 

		return 1;
	}	
		
	char buffer[1];
	int whitespace_flag = 0;
	int endoffile_flag = 0;
	words = 0;
	bytes = 0;
	lines = 0;

	while(!endoffile_flag)
	{
		int status_returned = read(file_discriptor, buffer, 1);
		if((status_returned != 1) && (errno > 0))
		{
			write_error_massage(errno,file_pathname); 
			
			return 1;
		}
		else
		{
			if(status_returned == 0)
			{
				endoffile_flag = 1;
				break;
			}

			bytes++;

			if((buffer[0] == ' ') || (buffer[0] == '\t') || (buffer[0] == '\n') || (buffer[0] == '\r'))	
				whitespace_flag = 0;
			else if(whitespace_flag == 0)
			{
				words++;
				whitespace_flag = 1;
			}

			if(buffer[0] == '\n')
				lines++;
		}
	}

	total_words += words;
	total_bytes += bytes;
	total_lines += lines;

	int close_status = close(file_discriptor);
	if((close_status == -1) && (errno > 0))
	{
		write_error_massage(errno, file_pathname);

		return 1;
	}
		
	return 0;
}

int get_counters_from_stdin(void)
{		
	char buffer[1];
	char reference[] = {'I', 'n', ' ', 'f', 'u', 'n', 'c', 't', 'i', 'o', 'n', ':', ' ', 'g', 'e', 't', '_', 'c', 'o', 'u', 'n', 't', 'e', 'r', 's', '_', 'f', 'r', 'o', 'm',  '_', 's', 't', 'd', 'i', 'n', '\0'};
	int whitespace_flag = 0;
	int endoffile_flag = 0;
	words = 0;
	bytes = 0;
	lines = 0;

	while(!endoffile_flag)
	{
		int status_returned = read(STDIN_FILENO, buffer, 1);
		if((status_returned != 1) && (errno > 0))
		{
			write_error_massage(errno, reference);
	 
			 return 1;
		}
		else
			if(status_returned == 0)
			{
				endoffile_flag = 1;
				break;
			}

			bytes++;

			if((buffer[0] == ' ') || (buffer[0] == '\t') || (buffer[0] == '\n') || (buffer[0] == '\r'))	
				whitespace_flag = 0;
			else if(whitespace_flag == 0)
			{
				words++;
				whitespace_flag = 1;
			}

			if(buffer[0] == '\n')
				lines++;
	}

	total_words += words;
	total_bytes += bytes;
	total_lines += lines;
	
	return 0;
}

int write_reference(char *reference, int stream)
{
	int i =0;
	int status_returned = 1;
	while(reference[i] != '\0')
	{
		if(stream == 1)
			status_returned = write(STDERR_FILENO, reference + i, 1);
		else
			status_returned = write(STDOUT_FILENO, reference + i, 1);

		i++;
		if((status_returned != 1) && (errno > 0))
		{
			write_error_massage(errno, reference);

			return 1;
		}
		
	}

	return 0;
}

int write_tab(int stream)
{
	char symbol[2];
	symbol[0] = '\t';
	symbol[1] = '\0';
	int status = 0;
	status = write_reference(symbol, stream);
	if(status == 1)
		return 1; 

	return 0;
}

int write_newline(int stream)
{
	char symbol[2];
	symbol[0] = '\n';
	symbol[1] = '\0';
	int status = 0;
	status = write_reference(symbol, stream);
	if(status == 1)
		return 1; 

	return 0;
}


int write_dots(int stream)
{
	char symbol[2];
	symbol[0] = ':';
	symbol[1] = '\0';
	int status = 0;
	status = write_reference(symbol, stream);
	if(status == 1)
		return 1; 

	return 0;
}

int write_wc(int stream)
{
	char symbols[3];
	symbols[0] = 'w';
	symbols[1] = 'c';
	symbols[2] = '\0';
	int status = 0;
	status = write_reference(symbols, stream);
	if(status == 1)
		return 1; 

	return 0;
}

int write_total(int stream)
{
	char symbols[] = {'t', 'o', 't', 'a', 'l', '\0'};
	int status = 0;
	status = write_reference(symbols, stream);
	if(status == 1)
		return 1;
 
	return 0;
}

void write_total_counters(int total_lines, int  total_words, int total_bytes)
{
	int stream = 0;
	int status = 0;
	status = write_tab(stream);
	if(status == 1)
		return; 
	status = write_counter(total_lines);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 
	status = write_counter(total_words);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 
	status = write_counter(total_bytes);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 
	status = write_total(stream);
	if(status == 1)
		return; 
	status = write_newline(stream);
	
	return;
}	

void wordcounter_file(char *file_pathname)
{
	int stream = 0;	
	int status = 0;
	status = get_counters_from_file(file_pathname);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 
	status = write_counter(lines);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 
	status = write_counter(words);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 
	status = write_counter(bytes);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 	
	status = write_reference(file_pathname, stream);
	if(status == 1)
		return; 
	status = write_newline(stream);

	return;	
}

void wordcounter_stdin(char *reference)
{
	int stream = 0;	
	int status = 0;
	status = get_counters_from_stdin();
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 	
	status = write_counter(lines);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 
	status = write_counter(words);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 
	status = write_counter(bytes);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 
	status = write_reference(reference, stream);
	if(status == 1)
		return; 
	status = write_newline(stream);

	return;
}

void write_error_massage(int error, char *reference)
{
	int stream = 1;	
	int status = 0;
	status = write_wc(stream);
	if(status == 1)
		return; 	 	
	status = write_dots(stream);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 	
	status = write_reference(reference, stream);
	if(status == 1)
		return; 	
	status = write_dots(stream);
	if(status == 1)
		return; 
	status = write_tab(stream);
	if(status == 1)
		return; 
	status = write_error(error);
	if(status == 1)
		return; 
	status = write_newline(stream);

	return;
}

int write_error(int error_number)
{
	int stream = 1;
	int status = 0;
	errno = 0;
	switch(error_number)
	{

		case 1:
		{			
			char error_massage[] = {'O', 'p', 'e', 'r', 'a', 't', 'i', 'o', 'n', ' ', 'n', 'o', 't', ' ', 'p', 'e', 'r', 'm', 'i', 't', 't', 'e', 'd', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 	
			break;
		}
		case 2 :
		{	
			char error_massage[] = {'N', 'o', ' ', 's', 'u', 'c', 'h', ' ', 'f', 'i', 'l', 'e', ' ', 'o', 'r', ' ', 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 	
			break;
		}
		case 4 :
		{	
			char error_massage[] = {'I', 'n', 't', 'e', 'r', 'r', 'u', 'p', 't', 'e', 'd', ' ', 's', 'y', 's', 't', 'e', 'm', ' ', 'c', 'a', 'l', 'l', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 	
			break;
		}
		case 5 :
		{	
			char error_massage[] = {'I', '/', 'O', ' ', 'e', 'r', 'r', 'o', 'r', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 	
			break;
		}
		case 6 :
		{
			char error_massage[] = {'N', 'o', ' ', 's', 'u', 'c', 'h', ' ', 'd', 'e', 'v', 'a', 'i', 'c', 'e', ' ', 'o', 'r', ' ', 'a', 'd', 'd', 'r', 'e', 's', 's', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 9 :
		{
			char error_massage[] = {'B', 'a', 'd', ' ', 'f', 'i', 'l', 'e', ' ', 'n', 'u', 'm', 'b', 'e', 'r', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 11 :
		{
			char error_massage[] = {'T', 'r', 'y', ' ', 'a', 'g', 'a', 'i', 'n', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 12 :
		{	
			char error_massage[] = {'O', 'u', 't', ' ', 'o', 'f', ' ', 'm', 'e', 'm', 'o', 'r', 'y', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 13 :
		{
			char error_massage[] = {'P', 'e', 'r', 'm', 'i', 's', 's', 'i', 'o', 'n', ' ', 'd', 'e', 'n', 'i', 'e', 'd', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 14 :
		{	
			char error_massage[] = {'B', 'a', 'd', ' ', 'a', 'd', 'd', 'r', 'e', 's', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 17 :
		{
			char error_massage[] = {'F', 'i', 'l', 'e', ' ', 'e', 'x', 'i', 's', 't', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 19 :
		{	
			char error_massage[] = {'N', 'o', ' ', 's', 'u', 'c', 'h', ' ', 'd', 'e', 'v', 'a', 'i', 'c', 'e', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 20 :
		{
			char error_massage[] = {'N', 'o', 't', ' ', 'a', ' ', 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 21 :
		{	
			char error_massage[] = {'I', 's', ' ', 'a', ' ', 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 22 :
		{	
			char error_massage[] = {'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ', 'a', 'r', 'g', 'u', 'm', 'e', 'n', 't', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 23 :
		{
			char error_massage[] = {'F', 'i', 'l', 'e', ' ', 't', 'a', 'b', 'l', 'e', ' ', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 26 :
		{
			char error_massage[] = {'T', 'e', 'x', 't', ' ', 'f', 'i', 'l', 'e', ' ', 'b', 'u', 's', 'y', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 27 :
		{
			char error_massage[] = {'F', 'i', 'l', 'e', ' ', 't', 'o', 'o', ' ', 'l', 'a', 'r', 'g', 'e', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 28 :
		{	
			char error_massage[] = {'N', 'o', ' ', 's', 'p', 'a', 'c', 'e', ' ', 'l', 'e', 'f', 't', ' ', 'o', 'n', ' ', 'd', 'e', 'v', 'a', 'i', 'c', 'e', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 30 :
		{
			char error_massage[] = {'R', 'e', 'a', 'd', ' ', 'o', 'n', 'l', 'y', ' ', 'f', 'i', 'l', 'e', ' ', 's', 'y', 's', 't', 'e', 'm', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 32 :
		{
			char error_massage[] = {'B', 'r', 'o', 'k', 'e', 'n', ' ', 'p', 'i', 'p', 'e', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 40 :
		{	
			char error_massage[] = {'T', 'o', 'o', ' ', 'm', 'a', 'n', 'y', ' ', 's', 'y', 'm', 'b', 'o', 'l', 'i', 'c', ' ', 'l', 'i', 'n', 'k', 's', ' ', 'e', 'n', 'c', 'o', 'u', 'n', 't', 'a',  'r', 'e', 'd', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 41 :
		{	
			char error_massage[] = {'O', 'p', 'e', 'r', 't', 'i', 'o', 'n', ' ', 'w', 'o', 'u', 'l', 'd', 'e', ' ', 'b', 'l', 'o', 'c', 'k', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 75 :
		{
			char error_massage[] = {'V', 'a', 'l', 'u', 'e', ' ', 't', 'o', 'o', ' ', 'l', 'a', 'r', 'g', 'e', ' ', 'f', 'o', 'r', ' ', 'd', 'e', 'f', 'a', 'i', 'n', 'e', 'd', ' ', 'd', 'a', 't', 'a', ' ', 't', 'y', 'p', 'e', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 89 :
		{
			char error_massage[] = {'D', 'e', 's', 't', 'n', 'a', 't', 'i', 'o', 'n', ' ', 'a', 'd', 'd', 'r', 'e', 's', 's', ' ', 'r', 'e', 'q', 'u', 'i', 'r', 'e', 'd', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 122 :
		{
			char error_massage[] = {'Q', 'o', 'a', 't', 'a', ' ', 'e', 'x', 'c', 'e', 'e', 'd', 'e', 'd', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;
		}
		case 125 :
		{
			char error_massage[] = {'u', 'n', 'r', 'e', 'c', 'o', 'g', 'n', 'i', 'z', 'e', 'd', ' ', 'o', 'p', 't', 'i', 'i', 'o', 'n', '\0'};
			status = write_reference(error_massage, stream);
			if(status == 1)
				return 1; 
			break;
		}
		default :
		{
			char error_massage[] = {'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ', 'e', 'r', 'r', 'o', 'r', ' ', 'o', 'c', 'u', 'r', 'r', 'e', 'd', '\0'};
			status = write_reference(error_massage, stream);	
			if(status == 1)
				return 1; 
			break;	
		}
	}
		
	return 0;
}
