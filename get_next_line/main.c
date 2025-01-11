
#include "stdlib.h" //malloc
#include "unistd.h" //write read
#include "fcntl.h" //open
#include "stdio.h" //printf
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

int ft_strlen(char *str)
{
	int i = -1;
	
	while (str[++i])
		;
	return (i);
}

int valid_breakline(char *str)
{
	int i = -1;
	
	while (str[++i])
	{
		if (str[i] == '\n')
			return (1);
	}
	return (0);
}

char *ft_strdup(char *input)
{
	char *str;
	int i = -1;

	str = (char *)malloc(sizeof(char) * ft_strlen(input) + 1);
	if (!str)
		return (NULL);
	while (input[++i])
		str[i] = input[i];
	str[i] = '\0';
	return (str);
}

char *ft_strjoin(char *first, char *second)
{
	char *str;
	int i = 0;
	int j = 0;

	str = (char *)malloc(sizeof(char) * (ft_strlen(first) + ft_strlen(second) + 1));
	if (!str)
		return (NULL);
	while (first[i])
	{
		str[i] = first[i];
		i++;
	}
	while (second[j])
	{
		str[i] = second[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *get_line (int fd, char *buffer, char *remainder)
{
	int status;
	char *tmp;

	while (1)
	{
		status = read(fd, buffer, BUFFER_SIZE);
		if (status == 0)
			break ;
		if (status < 0)
			return (NULL);
		buffer[status] = '\0';
		if (!remainder)
			remainder = ft_strdup("");
		tmp = ft_strjoin(remainder, buffer);
		free (remainder);
		remainder = ft_strdup(tmp);
		free (tmp);
		if (valid_breakline(buffer))
			break ;
	}
	return (remainder);
}

char *get_remainder(char *line)
{
	int i = -1;
	char *remainder;

	while(line[++i] != '\n' && line[i])
		;
	if (!line[i] || !line[++i])
		return (NULL);
	remainder = ft_strdup(line + i);
	line[i] = '\0';
	return (remainder);
}

char *get_next_line(int fd)
{
	char *buffer;
	char *line;
	static char *remainder;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = get_line(fd, buffer, remainder);
	free (buffer);
	if (!line)
	{
		free(remainder);
		return (NULL);
	}
	remainder = get_remainder(line);
	return (line);
}

// int main()
// {
// 	int fd;
// 	char *line;

// 	fd = open("./README.md", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s",line);
// 		free(line);
// 	}
// 	close (fd);

// 	int i = 0;
// 	if (i)
// 		printf("true");
// 	return (0);
// }

// fsanitizer=address -g
// valgrind --leak-check=yes ./a.out
