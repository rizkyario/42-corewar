/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_helper_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:28:03 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/30 14:23:52 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	*vm_memmark(void *dst, int i, size_t n)
{
	unsigned char *dst_p;

	dst_p = (unsigned char*)dst;
	while (n-- > 0)
		*dst_p++ = i;
	return (dst);
}

char
	*vm_to_big_endian(int value, int size)
{
	t_array	result;
	int		i;
	int		bits;

	i = 0;
	result = NEW_ARRAY(char);
	bits = size * 8;
	while (i <= bits - 8)
	{
		fta_append_char(&result, value >> (bits - 8 - i));
		i = i + 8;
	}
	return (result.data);
}

void
	vm_init_g_var(void)
{
	g_cycles = 1;
	g_cycles_to = 1;
	g_cycles_to_die = CYCLE_TO_DIE;
	g_carry = 0;
	ft_bzero(&g_memory, MEM_SIZE);
	ft_bzero(&g_reg, sizeof(int) * (MAX_PLAYERS * REG_NUMBER));
	ft_bzero(&g_memory_mark, MEM_SIZE);
}