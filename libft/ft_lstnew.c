/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:03:07 by gphilips          #+#    #+#             */
/*   Updated: 2016/11/19 15:26:54 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*dst;

	if (!(dst = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		dst->content_size = 0;
		dst->content = NULL;
	}
	else
	{
		dst->content_size = content_size;
		if (!(dst->content = (void*)malloc(sizeof(void) * content_size)))
			return (NULL);
		ft_memcpy(dst->content, content, content_size);
	}
	dst->next = NULL;
	return (dst);
}
