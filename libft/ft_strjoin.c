/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:32:08 by dgomez-a          #+#    #+#             */
/*   Updated: 2024/04/25 19:12:19 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;
	char	*join;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	i = 0;
	while (i <= len_s1)
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (i <= len_s2)
	{
		join[i + len_s1] = s2[i];
		i++;
	}
	join[len_s1 + len_s2 + 1] = '\0';
	return (join);
}
