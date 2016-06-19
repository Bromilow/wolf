#include "libft.h"

void	ft_memswap(void *a, void *b)
{
	void	*temp;

	temp = a;
	a    = b;
	b    = temp;
}
