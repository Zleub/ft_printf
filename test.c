#include <stdio.h>

int ft_printf(const char * restrict format, ...) ;

int main(void) {
	ft_printf("\t<%d>\n",
		ft_printf("%2s", "Hello !")
	);

	printf("\t<%d>\n",
		printf("%2s", "Hello !")
	);
}
