#include "libft.h"

void	ft_float_swap(float *a, float *b)
{
	float	t;
	t = *a;
	*a = *b;
	*b = t;
}
