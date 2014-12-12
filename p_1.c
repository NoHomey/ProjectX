#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int words;
int sym;
int lines;
char *buff;

int get_p(int count)
{
	//printf("%d\n",count);
	int i = 1;
	while(1)
	{

		if((count / i)  < 1)
		{
			return i;
		}
		else
		{
			
		}
		i = i*10;
		
	}
}
void print_c(int count)
{
	int d = get_p(count)/10;
	//printf("%d\n",d);
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

int get_size(char * name)
{
	int size;
	struct stat st;
	stat(name, &st);
	size = st.st_size;
	return size;
}

char * make_buff(char * name)
{
	int size = get_size(name);
	buff = (char *) malloc(sizeof(char) * size);
	int fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		perror("open()");
		return ;
	}
	int status_read = read(fd, buff, size);

	int close_status = close(fd);
	if (close_status == -1)
	{
		perror("close()");
		return ;
	}
	
	return buff;

}

void get_cs(char buff[], char *name)
{
	int size = get_size(name);
	words = 0;
	sym = 0;
	lines = 0;
	int i = 0;
	for(i =0;i < size;i++)
	{
		
		if(buff[i] == '\n')
			lines++;
		if(((buff[i] == '\n') && ((buff[i - 1] != '\n') || (buff[i - 1] != '\t') || (buff[i - 1] != ' ')))  || ((buff[i] == '\t') && ((buff[i - 1] != '\n') || (buff[i - 1] != '\t') || (buff[i - 1] != ' '))) || ((buff[i] == ' ') && ((buff[i - 1] != '\n') || (buff[i - 1] != '\t') || (buff[i - 1] != ' '))))
			words++;
		if((buff[i] >= 0) && (buff[i] <= 255))
			sym++;
	}	

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

wc_file(char *n)
{
	char s[2];
	s[0] = ' ';
	s[1] = '\n';
	
	get_cs(make_buff(n),n);
	print_c(lines);
	write(STDOUT_FILENO, s, 1);
	print_c(words);
	write(STDOUT_FILENO, s, 1);
	print_c(sym);
	write(STDOUT_FILENO, s, 1);
	print_n(n);
	write(STDOUT_FILENO, s + 1, 1);
}
int main()
{

	
	char n[10];
	n[0] = 'a';
	n[1] = '.';
	n[2] = 't';
	n[3] = 'x';
	n[4] = 't';
	n[5] = '\0';
	
	wc_file(n);

	return 0;
}
