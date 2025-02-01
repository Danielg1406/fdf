#include "libft.h"

// TODO: Add Header and do Norminette check
static int	ft_is_valid_char(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c < '0' + base);
	return ((c >= '0' && c <= '9') || (c >= 'A' && c < 'A' + base - 10) || (c >= 'a' && c < 'a' + base - 10));
}

static int	ft_char_to_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (0);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;

	if (base < 2 || base > 16)
		return (0);
	result = 0;
	sign = 1;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (base == 16 && *str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	while (*str && ft_is_valid_char(*str, base))
	{
		result = result * base + ft_char_to_value(*str);
		str++;
	}
	return (result * sign);
}
