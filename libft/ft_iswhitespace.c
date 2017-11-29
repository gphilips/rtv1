#include "libft.h"

int		ft_iswhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
			|| c == '\r');
}
