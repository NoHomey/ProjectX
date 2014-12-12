#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int words;
int sym;
int lines;
int total_words;
int total_sym;
int total_lines;


void print_error(int e)
{
	switch(e)
	{
		case 2 :
		{
			char m[] = {'N', 'o', ' ', 's', 'u', 'c', 'h', ' ', 'f', 'i', 'l', 'e', ' ', 'o', 'r', ' ', 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y'};
			write(STDERR_FILENO, m, 25);
			break;
		}
		case 13 :
		{
			char m[] = {'P', 'e', 'r', 'm', 'i', 's', 's', 'i', 'o', 'n', ' ', 'd', 'e', 'n', 'i', 'e', 'd'};
			write(STDERR_FILENO, m, 17);
			break;
		}
	}
		

}

int get_p(int count)
{

	int i = 1;
	while(1)
	{

		if((count / i)  < 1)
		{
			return i;
		}
		i = i*10;
		
	}
}
void print_c(int count)
{
	int d = get_p(count)/10;
	char c[1];
	if(d == 1)
	{
		while(count > 0)
		{
			c[0] = (count % 10) + 48;
			if(c[0] >= 48 && c[0] <= 57)
				write(STDOUT_FILENO, c, 1);
		
			count = count/10;
		}
	}
	else
	{
		while(d > 0)
		{
			c[0] = (count/d) + 48;
			if(c[0] >= 48 && c[0] <= 57)
				write(STDOUT_FILENO, c, 1);
		
			count = count%d;
			d = d/10;

		}
	}
}

int get_cs_file(char * name)
{

	int fd = open(name, O_RDONLY);
	if (fd == -1)
	{	
		return errno;
			
	}

	char buff[1];
	int flag = 0;
	int eof = 0;
	words = 0;
	sym = 0;
	lines = 0;
	while(!eof)
	{

		int r = read(fd, buff, 1);
		if(r == 0)
		{
			eof = 1;
			break;
		}
		sym++;
		if((buff[0] == ' ') || (buff[0] == '\t') || (buff[0] == '\n') || (buff[0] == '\r'))	
		{
			flag = 0;
		}
		else if(flag == 0)
		{
			words++;
			flag = 1;
		}
		if(buff[0] == '\n')
			lines++;
	}

	total_words += words;
	total_sym += sym;
	total_lines += lines;


	int close_status = close(fd);
	if (close_status == -1)
	{
		perror("close()");
		return 4;
	}
		
	return 0;
}

void get_cs_stdin(void)
{
	char buff[1];
	int flag = 0;
	int eof = 0;
	words = 0;
	sym = 0;
	lines = 0;
	while(!eof)
	{

		int r = read(STDIN_FILENO, buff, 1);
		if(r == 0)
		{
			eof = 1;
			break;
		}
		sym++;
		if((buff[0] == ' ') || (buff[0] == '\t') || (buff[0] == '\n') || (buff[0] == '\r'))	
		{
			flag = 0;
		}
		else if(flag == 0)
		{
			words++;
			flag = 1;
		}
		if(buff[0] == '\n')
			lines++;
	}

	total_words += words;
	total_sym += sym;
	total_lines += lines;	

}


void print_n(char *name)
{
	int i =0;
	while(name[i] != '\0')
	{
		write(STDOUT_FILENO, name + i, 1);
		i++;
	}
}

void wc_stdin(void)
{
	char s[3];
	s[0] = ' ';
	s[1] = '\n';
	s[2] = '-';
	get_cs_stdin();
	print_c(lines);
	write(STDOUT_FILENO, s, 1);
	print_c(words);
	write(STDOUT_FILENO, s, 1);
	print_c(sym);
	write(STDOUT_FILENO, s, 1);
	write(STDOUT_FILENO, s + 2, 1);
	write(STDOUT_FILENO, s + 1, 1);
}

void wc_file(char *n)
{
	char s[3];
	s[0] = ' ';
	s[1] = '\n';
	s[2] = ':';
	
	int err = get_cs_file(n);
	if(err != 0)
	{
		write(STDOUT_FILENO, s, 1);		
		print_n(n);		
		write(STDOUT_FILENO, s + 2, 1);
		write(STDOUT_FILENO, s, 1);	
		print_error(err);
		write(STDOUT_FILENO, s + 1, 1);
		
	}
	else
	{
		print_c(lines);
		write(STDOUT_FILENO, s, 1);
		print_c(words);
		write(STDOUT_FILENO, s, 1);
		print_c(sym);
		write(STDOUT_FILENO, s, 1);
		print_n(n);
		write(STDOUT_FILENO, s + 1, 1);
	}
}

void print_total(int total_lines, int total_words, int total_sym)
{
	char s[2];
	s[0] = ' ';
	s[1] = '\n';
	char t[] = {'t', 'o', 't', 'a', 'l'};	
	print_c(total_lines);
	write(STDOUT_FILENO, s, 1);
	print_c(total_words);
	write(STDOUT_FILENO, s, 1);
	print_c(total_sym);
	write(STDOUT_FILENO, s, 1);
	write(STDOUT_FILENO, t, 5);
	write(STDOUT_FILENO, s + 1, 1);
}
int main(int argc,char *argv[])
{
	int i;
	int total_flag = 1;
	
	if(argc < 3)
	{
		total_flag = 0;
	}
	
	for(i = 1;i < argc;i++)
	{
		if(argv[i][0] == '-')
			wc_stdin();
		else
			wc_file(argv[i]);
	}

	if(total_flag == 1)
		print_total(total_lines, total_words, total_sym);
	return 0;
}
