#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

enum e_flags {
	SHARP = 1,
	ZERO = 2,
	MINUS = 4,
	PLUS = 8,
	SPACE = 16,
	FLAGS_LEN = 24
};

void ft_bzero(void *p, size_t s)
{
	size_t i;

	i = 0;
	while (i < s)
	{
		((char*)p)[i] = 0;
		i += 1;
	}
}

int ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i += 1;
	return (i);
}

void ft_putstr(const char *s)
{
	write(1, s, ft_strlen(s));
}


char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	if (c == '\0')
		return (char*)(s + ft_strlen(s));
	while (s[i]) {
		if (s[i] != (unsigned char)c)
			i += 1;
		else
			return (char*)(s + i);
	}
	return (NULL);
}

static void		reverse(char *str, int length)
{
	int			i;
	int			j;
	char		tmp;

	i = 0;
	j = length - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

char			*ft_itoa(int n)
{
	char		*result;
	int			sign;
	int			i;

	if (n == -2147483648)
		return ("-2147483648");
	sign = n < 0 ? 1 : 0;
	i = 0;
	result = malloc(sizeof(char *) * 12);
	if (n == 0)
		result[i++] = '0';
	else if (n < 0)
	{
		result[i++] = '-';
		n = -n;
	}
	while (n > 0)
	{
		result[i++] = '0' + n % 10;
		n /= 10;
	}
	reverse(result + sign, i - sign);
	result[i] = '\0';
	return (result);
}

char	*ft_strcpy(char *s1, const char *s2)
{
	char	*p;

	p = s1;
	while (*s2 != '\0')
	{
		*s1++ = *s2++;
	}
	*s1 = '\0';
	return (p);
}






int ft_writechar(va_list args, char *s)
{
	int c = (int)(va_arg(args, int));
	*s = c;
	return (1);
}

int ft_writeint(va_list args, char *s)
{
	int i = va_arg(args, int);
	char *tmp = ft_itoa(i);
	int len = ft_strlen(tmp);

	ft_strcpy(s, tmp);
	free(tmp);
	return (len);
}

int ft_writestring(va_list args, char *s)
{
	char *tmp = va_arg(args, char *);

	ft_strcpy(s, tmp);
	return (ft_strlen(tmp));
}

int ft_writewidestring(va_list args, char *s)
{
	wchar_t *tmp = va_arg(args, wchar_t *);
	(void)tmp;
	(void)s;

	int i = 0;
	// while (tmp[i]) {
	// 	s[i] = tmp[i];
	// 	i += 1;
	// }
	return (i);
}

int ft_writepercent(va_list args, char *s)
{
	(void)args;
	*s = '%';
	return (1);
}

struct {
	char c;
	int (*f)(va_list args, char *s);
} matches[] = {
	{ '%', ft_writepercent },
	{ 's', ft_writestring },
	{ 'S', ft_writewidestring },
	{ 'p', NULL },
	{ 'd', ft_writeint },
	{ 'D', NULL },
	{ 'i', NULL },
	{ 'o', NULL },
	{ 'O', NULL },
	{ 'u', NULL },
	{ 'U', NULL },
	{ 'x', NULL },
	{ 'X', NULL },
	{ 'c', ft_writechar },
	{ 'C', NULL },
	{ '\0', NULL }
};

int match(va_list args, char *s, char c)
{
	int i;

	i = 0;
	while (matches[i].c)
	{
		if (matches[i].c == c && matches[i].f)
			return matches[i].f(args, s);
		i += 1;
	}

	return (0);
}

int ft_printf(const char * restrict format, ...) {
	va_list a_list;
	int i;

	va_start(a_list, format);
	i = 0;

	char str[1024];
	ft_bzero(str, 1024);

	char *s = str;

	char *tmp = ft_strchr(format, '%');
	if (!tmp)
		return (s - str);
	char next = *tmp;
	(void)next;
	while (i < ft_strlen(format) && next != 'S') {
		if (format[i] == '%') {
			// if (format[i + 1] == 'S') {
			// 	va_end(a_list);
			// 	write(1, str, 1024);
			// 	return (0);
			// }
			s += match(a_list, s, format[i + 1]);
			// next = ft_strchr(&format[i + 1], '%')[1];
			i += 1;
		}
		else {
			*s = format[i];
			s += 1;
		}
		i += 1;
	}
	va_end(a_list);
	write(1, str, s - str);
	return (s - str);
}
