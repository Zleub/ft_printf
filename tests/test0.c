#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

int ft_printf(const char * restrict format, ...);

int main(void) {
	// ft_printf("Hello World !\n");
	// printf("Hello World !\n");

	write(1, "\0", 1);
	// ft_printf("");
	printf("");

	// ft_printf("%%\n");
	// printf("%%\n");
    //
	// ft_printf("%c\n", 42);
	// printf("%c\n", 42);
    //
	// ft_printf("%d\n", 42);
	// printf("%d\n", 42);
    //
	// ft_printf("%s\n", "quarante deux");
	// printf("%s\n", "quarante deux");
    //
	// ft_printf("%42s\n", "quarante deux");
	// printf("%42s\n", "quarante deux");
    //
	// ft_printf("%4s\n", "quarante deux");
	// printf("%4s\n", "quarante deux");
    //
	// ft_printf("%s\n", "john 麥克風");
	// printf("%s\n", "john 麥克風");
    //
	// ft_printf("%S\n", L"john 麥克風");
	// printf("%S\n", L"john 麥克風");
    //
	// ft_printf("%S %d\n", L"£100 π", 42);
	// printf("%S %d\n", L"£100 π", 42);
    //
	// ft_printf("%d %S\n", 42, L"£100 π");
	// ft_printf("\n");
	// printf("%d %S\n", 42, L"£100 π");
	// printf("\n");

	return (0);
}
