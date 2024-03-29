/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:16:34 by zkepes            #+#    #+#             */
/*   Updated: 2024/02/29 14:50:50 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*Shift up all elements of stack (head) by 1.The first element becomes the last
one, if there are at least two nodes*/
void	co_rotate_a(t_node **head)
{
	if (ch_2_nodes(&(*head)))
	{
		*head = (*head)->next;
		write(1, "ra\n", 3);
	}
}

void	co_rotate_b(t_node **head)
{
	if (ch_2_nodes(&(*head)))
	{
		*head = (*head)->next;
		write(1, "rb\n", 3);
	}
}

/*rotates both stacks if there are at least two nodes in each*/
void	co_rotate_both(t_node **head_a, t_node **head_b)
{
	if (ch_2_nodes(&(*head_a)) && ch_2_nodes(&(*head_b)))
	{
		*head_a = (*head_a)->next;
		*head_b = (*head_b)->next;
		write(1, "rr\n", 3);
	}
}
