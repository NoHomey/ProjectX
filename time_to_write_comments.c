//--------------------------------------------
// NAME: Ivan Ivanov
// CLASS: XIa
// NUMBER: 13
// PROBLEM: #1
// FILE NAME: xxxxxx.yyy.zzz (unix file name)
// FILE PURPOSE:
// няколко реда, които описват накратко
// предназначението на файла
// ...
//---------------------------------------------

//--------------------------------------------
// HEADER: <sys/types.h>
// предназначение на функцията
//----------------------------------------------
#include <sys/types.h>	
//--------------------------------------------
// HEADER: <sys/types.h>
// предназначение на функцията
//----------------------------------------------	
#include <sys/stat.h>	
//--------------------------------------------
// HEADER: <sys/types.h>
// предназначение на функцията
//---------------------------------------------- 	
#include <fcntl.h>
//--------------------------------------------
// HEADER: <sys/types.h>
// предназначение на функцията
//----------------------------------------------		
#include <stdio.h>
//--------------------------------------------
// HEADER: <sys/types.h>
// предназначение на функцията
//----------------------------------------------		
#include <unistd.h>
//--------------------------------------------
// HEADER: <sys/types.h>
// предназначение на функцията
//----------------------------------------------		
#include <errno.h>

//--------------------------------------------
// VARIBLE: words
// предназначение на функцията
//----------------------------------------------
int words = 0;
//--------------------------------------------
// VARIBLE: words
// предназначение на функцията
//----------------------------------------------	
int bytes = 0;
//--------------------------------------------
// VARIBLE: words
// предназначение на функцията
//----------------------------------------------	
int lines = 0;	
//--------------------------------------------
// VARIBLE: words
// предназначение на функцията
//----------------------------------------------	
int total_words = 0;
//--------------------------------------------
// VARIBLE: words
// предназначение на функцията
//----------------------------------------------		
int total_bytes = 0;
//--------------------------------------------
// VARIBLE: words
// предназначение на функцията
//----------------------------------------------					
int total_lines = 0;	

//--------------------------------------------
// FUNCTION: get_extention
// предназначение на функцията
// PARAMETERS:
// counter:
// 
//----------------------------------------------
int get_extention(int counter);	
//--------------------------------------------
// FUNCTION: write_counter
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------							
int write_counter(int counter);
//--------------------------------------------
// FUNCTION: get_counters_from_file
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------							
int get_counters_from_file(char *file_pathname);
//--------------------------------------------
// FUNCTION: get_counters_from_stdin
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------					
int get_counters_from_stdin(void);	
//--------------------------------------------
// FUNCTION: write_reference
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------						
int write_reference(char *reference, int stream);
//--------------------------------------------
// FUNCTION: write_space
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------					
int write_space(int stream);	
//--------------------------------------------
// FUNCTION: write_newline
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------								
int write_newline(int stream);	
//--------------------------------------------
// FUNCTION: write_dots
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------						
int write_dots(int stream);
//--------------------------------------------
// FUNCTION: write_wc
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------								
int write_wc(int stream);	
//--------------------------------------------
// FUNCTION: write_total
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------									
int write_total(int stream);	
//--------------------------------------------
// FUNCTION: write_total_counters
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------								
void write_total_counters(int total_lines, int total_words, int total_bytes);
//--------------------------------------------
// FUNCTION: wordcounter_file
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------
void wordcounter_file(char *file_pathname);
//--------------------------------------------
// FUNCTION: wordcounter_stdin
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------						
void wordcounter_stdin(char *reference);
//--------------------------------------------
// FUNCTION: write_error
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------						
int write_error(int error_number);
//--------------------------------------------
// FUNCTION: write_error_massage
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------							
void write_error_massage(int error, char *reference);					

//--------------------------------------------
// FUNCTION: main
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//----------------------------------------------
int main(int argc,char **argv)
{
	int i;
	int total_flag = 1;
	char stdin_name[1] = {'\0'};

	if(argc < 3)
		total_flag = 0;

	if(argc == 1)
		wordcounter_stdin(stdin_name);
		
	for(i = 1;i < argc;i++)
	{
		if((argv[i][0] == '-') && (argv[i][1] == '\0'))
			wordcounter_stdin(argv[i]);
			
		else
			wordcounter_file(argv[i]);		 
	}

	if(total_flag == 1)
		write_total_counters(total_lines, total_words, total_bytes);
		
	return 0;
}

int get_extention(int counter)
{
	int i = 1;
	while(1)
	{
		if((counter / i)  < 1)
			return (i / 10);

		i = i*10;	
	}
}

int write_counter(int counter)
{
	int counter_extention = get_extention(counter);
	char digit_to_char[1];
	char reference[] = {'I', 'n', ' ', 'f', 'u', 'n', 'c', 't', 'i', 'o', 'n', ':', ' ', 'w', 'r', 'i', 't', 'e', '_', 'c', 'o', 'u', 'n', 't', 'e', 'r', '\0'};
	if(counter_extention <= 0)
	{
		digit_to_char[0] = 48;
		int status_returned = write(STDOUT_FILENO, digit_to_char, 1);
				if((status_returned != 1) && (errno > 0))
				{
					write_error_massage(errno, reference);
	
					return 1;
				}
	}
	else if(counter_extention == 1)
	{
		while(counter > 0)
		{
			digit_to_char[0] = (counter % 10) + 48;
			counter = counter / 10;
			if(digit_to_char[0] >= 48 && digit_to_char[0] <= 57)
			{
				int status_returned = write(STDOUT_FILENO, digit_to_char, 1);
				if((status_returned != 1) && (errno > 0))
				{
					write_error_massage(errno, reference);	
			
					return 1;
				}
			}
		}
	}
	else
	{
		while(counter_extention > 0)
		{
			digit_to_char[0] = (counter / counter_extention) + 48;
			counter = counter % counter_extention;
			counter_extention = counter_extention / 10;
			if(digit_to_char[0] >= 48 && digit_to_char[0] <= 57)
			{
				int status_returned = write(STDOUT_FILENO, digit_to_char, 1);
				if((status_returned != 1) && (errno > 0))
				{
					write_error_massage(errno, reference);

					return 1;
				}
			}
		}
	}

	return 0;
}

int get_counters_from_file(char * file_pathname)
{	
	int file_discriptor = open(file_pathname, O_RDONLY);
	if(file_pathname[0] == '-')
		errno = 22;
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

int write_space(int stream)
{
	char symbol[2];
	symbol[0] = ' ';
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
	status = write_space(stream);
	if(status == 1)
		return; 
	status = write_counter(total_lines);
	if(status == 1)
		return; 
	status = write_space(stream);
	if(status == 1)
		return; 
	status = write_counter(total_words);
	if(status == 1)
		return; 
	status = write_space(stream);
	if(status == 1)
		return; 
	status = write_counter(total_bytes);
	if(status == 1)
		return; 
	status = write_space(stream);
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
	status = write_space(stream);
	if(status == 1)
		return; 
	status = write_counter(lines);
	if(status == 1)
		return; 
	status = write_space(stream);
	if(status == 1)
		return; 
	status = write_counter(words);
	if(status == 1)
		return; 
	status = write_space(stream);
	if(status == 1)
		return; 
	status = write_counter(bytes);
	if(status == 1)
		return; 
	status = write_space(stream);
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
	status = write_space(stream);
	if(status == 1)
		return; 	
	status = write_counter(lines);
	if(status == 1)
		return; 
	status = write_space(stream);
	if(status == 1)
		return; 
	status = write_counter(words);
	if(status == 1)
		return; 
	status = write_space(stream);
	if(status == 1)
		return; 
	status = write_counter(bytes);
	if(status == 1)
		return; 
	status = write_space(stream);
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
	status = write_space(stream);
	if(status == 1)
		return; 	
	status = write_reference(reference, stream);
	if(status == 1)
		return; 	
	status = write_dots(stream);
	if(status == 1)
		return; 
	status = write_space(stream);
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
