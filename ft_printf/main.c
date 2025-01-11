
#include "stdio.h" //printf
#include "stdarg.h" //va_arg
#include "unistd.h" //write

int ft_catch_string(char *str)
{
	int i = -1;

	if (!str)
	{
		i = write (1, "(null)", 6);
		return (i);
	}
	while (str[++i])
		write (1, &str[i], 1);
	return (i);
}

void ft_print_decimal(int nbr)
{
	char digit;

	if (nbr > 9)
	{
		ft_print_decimal(nbr/10);
		ft_print_decimal(nbr%10);
	}
	else
	{
		digit = nbr + '0';
		write (1, &digit, 1);
	}
}

int ft_catch_decimal(int nbr)
{
	int i = 1;
	// 2147483647, -2147483648
	if (nbr == -2147483648)
	{
		i = write (1, "-2147483648", 11);
	}
	else
	{
		if (nbr < 0)
		{
			i++;
			write (1, "-", 1);
			nbr *= -1;
		}
		ft_print_decimal(nbr);//TODO
		while (nbr > 9)
		{
			nbr /= 10;
			i++;
		}
	}
	return (i);
}

void ft_print_hexadecimal(unsigned int nbr)
{
	char *hex = "0123456789abcdef";

	if (nbr >= 16)
	{
		ft_print_hexadecimal(nbr/16);
		ft_print_hexadecimal(nbr%16);
	}
	else
	{
		write (1, &hex[nbr], 1);
	}
}

int ft_catch_hexadecimal(unsigned int nbr)
{
	int i = 1;

	ft_print_hexadecimal(nbr);
	while (nbr >= 16)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

int valid_parameter(char param, va_list *ap)
{
	int length = 0;

	if (param == 's')
		length = ft_catch_string(va_arg(*ap, char *));
	else if (param == 'd')
		length = ft_catch_decimal(va_arg(*ap, int));
	else if (param == 'x')
		length = ft_catch_hexadecimal(va_arg(*ap, unsigned int));
	else
		length = write(1, &param, 1);

	return (length);
}

int ft_printf(const char *param, ... )
{
	va_list ap;
	int length = 0;

	va_start(ap, param);
	while (*param)
	{
		if (*param == '%')
			length += valid_parameter(*(++param), &ap);//TODO
		else
			length += write(1, &(*param), 1);
		param++;
	}
	va_end(ap);

	return (length);
}

// int main()
// {
// 	// int size = 0;
// 	// char *str = "hellos";
// 	// size = ft_printf("%s_123\n", str);
// 	// printf("size=%d\n", size);
// 	// size = printf("%s_123\n", str);
// 	// printf("size=%d\n", size);

// 	// int size = 0;
// 	// char *str = NULL;
// 	// size = ft_printf("%s_123\n", str);
// 	// printf("size=%d\n", size);
// 	// size = printf("%s_123\n", str);
// 	// printf("size=%d\n", size);

// 	// int size = 0;
// 	// int number = -2147483647;
// 	// size = ft_printf("%d_abc\n", number);
// 	// printf("size=%d\n", size);
// 	// size = printf("%d_abc\n", number);
// 	// printf("size=%d\n", size);

// 	int size = 0;
// 	int number = -200;
// 	size = ft_printf("%x_abc\n", number);
// 	printf("size=%d\n", size);
// 	size = printf("%x_abc\n", number);
// 	printf("size=%d\n", size);
// 	return (0);
// }
