#include <stdio.h>
#include "libft/libft.h"

void	of_free_arr(void **arr, int self_free)
{
	int	i;

	if (arr == NULL)
		return;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	if (self_free == 1 && arr != NULL)
		free(arr);
}

int main() {
    const char str[] = "Hallo ein Test wird hier gemacht";
    char **splitted;
   
    splitted = ft_split(str, ' '  );
    of_free_arr((void **)splitted, 1);
    return 0;
}
