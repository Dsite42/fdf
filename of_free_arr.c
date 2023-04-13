/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   of_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:50:37 by chris             #+#    #+#             */
/*   Updated: 2023/04/13 17:49:12 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The function of_free_arr frees all contents of an void **array and itself.
// Return: none.
#include "fdf.h"

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
