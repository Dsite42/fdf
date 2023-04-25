
#include "../fdf.h"

int	ft_nb_exp(char c, char *base, int e_base, int exp)
{
	int	i;
	int	res;
	int	nb;

	i = 0;
	while (c != base[i])
		i++;
	nb = i;
	if (exp == 0)
		return (nb * 1);
	i = 1;
	res = e_base;
	while (i < exp)
	{
		res = res * e_base;
		i++;
	}
	return (nb * res);
}

int	is_spmn(char *str, int *c_min)
{
	int		i;

	i = 0;
	while ((str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v'))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*c_min = *c_min + 1;
		i++;
	}
	return (i);
}

int	check_base(char *base, int *base_len)
{
	int	i;
	int	j;

	i = 0;
	while (*(base + i) != '\0')
		i++;
	*base_len = i;
	i = 0;
	j = 1;
	if (*base_len <= 1)
		return (0);
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == ' ')
			return (0);
		while (base[j] != '\0' && (i + j) < *base_len)
		{
			if (base[i] == base[i + j])
				return (0);
			j++;
		}
		j = 1;
		base++;
	}
	return (1);
}

int	transf_to_int(char *str, char *base, int *base_len)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = 0;
	res = 0;
	while (base[i] != '\0')
	{
		if (base[i] == str[j])
		{
			j++;
			i = -1;
		}
		i++;
	}
	i = 0;
	while (i < j)
	{
		res = res + ft_nb_exp(str[i], base, *base_len, j - i -1);
		i++;
	}
	return (res);
}

int	of_atoi_base(char *str, char *base)
{
	int	start_n;
	int	res;
	int	c_min;
	int	base_len;

	start_n = is_spmn (str, &c_min);
	if (check_base(base, &base_len) == 0)
		return (0);
	res = transf_to_int(&str[start_n], base, &base_len);
	if (c_min % 2 == 1)
		res = res * -1;
	return (res);
}
