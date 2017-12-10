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

typedef struct s_printf t_printf;
struct s_printf {
	int padding;
	int plus;
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

int			ft_atoi(const char *str)
{
	int		i;
	int		nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	i = 0;


	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = 10 * nbr + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
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

char			*ft_itoa(int n)
{
	char		*result;
	int			sign;
	int			i;

	result = malloc(sizeof(char) * 12);
	ft_bzero(result, 12);
	if (n == -2147483648)
		return (ft_strcpy(result, "-2147483648"));
	sign = n < 0 ? 1 : 0;
	i = 0;
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

char			*ft_utoa(unsigned int n)
{
	char		*result;
	unsigned int			i;

	result = malloc(sizeof(char) * 12);
	ft_bzero(result, 12);
	i = 0;
	if (n == 0)
		result[i++] = '0';
	while (n > 0)
	{
		result[i++] = '0' + n % 10;
		n /= 10;
	}
	reverse(result, i);
	result[i] = '\0';
	return (result);
}




void print_struct(t_printf *arg)
{
	printf(
		"t_printf %p:\n"
		"\tpadding: %d\n",
		arg,
		arg->padding
	);
}

int count_digit(const char *s)
{
	int i;

	i = 0;
	while ( s[i] && ((s[i] >= '0' && s[i] <= '9') || s[i] == '-') )
		i += 1;
	return (i);
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

int ft_writeunsigned(va_list args, char *s)
{
	unsigned int i = va_arg(args, unsigned int);
	char *tmp = ft_utoa(i);
	int len = ft_strlen(tmp);

	ft_strcpy(s, tmp);
	free(tmp);
	return (len);
}

int ft_writestring(va_list args, char *s)
{
	char *tmp = va_arg(args, char *);

	if (!tmp) {
		ft_strcpy(s, "(null)");
		return (6);
	}
	else
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
	{ 'u', ft_writeunsigned },
	{ 'U', NULL },
	{ 'x', NULL },
	{ 'X', NULL },
	{ 'c', ft_writechar },
	{ 'C', NULL },
	{ '\0', NULL }
};

int match(va_list args, char *s, char c, t_printf *arg)
{
	int i;

	i = 0;
	(void)arg;
	while (matches[i].c)
	{
		if (matches[i].c == c && matches[i].f) {
			int len = matches[i].f(args, s);
			char _[len + 2];
			ft_bzero(_, len + 2);

			if (arg->padding >= 0) {

				int plus = 0;
				if (arg->plus && s[0] != '-') {
					plus = 1;
					ft_strcpy(_, "+");
					ft_strcpy(_ + 1, s);
				}
				else
					ft_strcpy(_, s);

				int padding = (arg->padding - len);
				while (padding > -1 - arg->plus) {
					s[padding] = ' ';
					padding -= 1;
				}
				if (arg->padding - len > 0)
					ft_strcpy(&s[arg->padding - len - arg->plus - plus], _);

				if (arg->padding > len)
					return (arg->padding - arg->plus);
				return (len - arg->plus);

			}
			else {
				int padding = (arg->padding * -1) - len;
				char padstring[padding];

				int i = 0;
				while (i < padding) {
					padstring[i] = ' ';
					i += 1;
				}

				ft_strcpy(&s[len], padstring);
				return (len + padding);
			}
		}
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
	int len = ft_strlen(format);
	while (i < len) {
		if (format[i] == '%') {
			t_printf arg;
			i += 1;

			ft_bzero(&arg, sizeof(t_printf));
			if (format[i] == '0')
				;
				// printf("got it\n");
			if (format[i] == '+') {
				// printf("got plus\n");
				arg.plus = 1;
				s += 1;
				i += 1;
			}
			// if (format[i] == '-') {
				// printf("got plus\n");
				// arg.minus = 1;
				// s += 1;
				// i += 1;
			// }


			arg.padding = ft_atoi(&format[i]);

			i += count_digit(&format[i]);
			s += match(a_list, s, format[i], &arg);
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
