/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_decompiler_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 20:42:42 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/03 10:54:25 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int
	vm_binary_toint(unsigned char *bin, int size)
{
	int		i;
	int		result;

	i = 1;
	result = 0;
	while (i <= size)
	{
		result += bin[i - 1] << ((size - i) * 8);
		i++;
	}
	return (result);
}

int
	vm_read_magic(int fd, t_champ *champ)
{
	int				ret;
	unsigned char	buf[COMMENT_LENGTH + 4];

	if ((ret = read(fd, &buf, 4)) <= 0)
		return (INVALID_MAGIC);
	champ->header.magic = vm_binary_toint(buf, 4);
	if (vm_binary_toint(buf, 4) != COREWAR_EXEC_MAGIC)
		return (INVALID_MAGIC);
	return (0);
}

int
	vm_read_header(int fd, t_champ *champ)
{
	int				ret;
	unsigned char	buf[COMMENT_LENGTH + 4];

	if (vm_read_magic(fd, champ) > 0)
		return (INVALID_MAGIC);
	if ((ret = read(fd, &buf, PROG_NAME_LENGTH + 4)) <= 0)
		return (INVALID_HEADER);
	ft_strncpy(champ->header.prog_name, (char*)buf, PROG_NAME_LENGTH + 4 + 1);
	if ((ret = read(fd, &buf, 4) <= 0))
		return (INVALID_HEADER);
	champ->header.prog_size = vm_binary_toint(buf, 4);
	if (champ->header.prog_size > CHAMP_MAX_SIZE)
		return (CODE_MAX);
	if ((ret = read(fd, &buf, COMMENT_LENGTH + 4)) <= 0)
		return (INVALID_HEADER);
	ft_strncpy(champ->header.comment, (char*)buf, COMMENT_LENGTH + 4 + 1);
	return (0);
}

static int
	vm_free_err(t_vm *vm, int max, int errnum, char *file)
{
	int i;

	i = 0;
	while (i < max)
	{
		free(vm->champ[i].op);
		fta_clear(&(vm->processes));
		i++;
	}
	if (errnum == MALLOC)
		return (vm_error(errnum, -1, NULL));
	return (vm_error(errnum, -1, file));
}

int
	vm_read_binaries(char **paths, t_vm *vm)
{
	int				fd;
	unsigned char	buf[COMMENT_LENGTH + 4];
	t_champ			champ;
	int				i;
	int				error;

	i = -1;
	error = 0;
	while (++i < vm->champ_size)
	{
		if ((fd = open(paths[i], O_RDONLY)) == -1)
			error = INVALID_FILE;
		else if ((error = vm_read_header(fd, &champ)) > 0)
			;
		else if (read(fd, &buf, champ.header.prog_size) <
			champ.header.prog_size)
			error = INVALID_INSTR;
		else if (read(fd, &buf, 1) > 0)
			error = INVALID_INSTR;
		else if ((champ.op = ft_memalloc(champ.header.prog_size + 1)) == NULL)
			error = MALLOC;
		if (error)
			return (vm_free_err(vm, i, error, paths[i]));
		ft_memcpy(champ.op, buf, champ.header.prog_size + 1);
		champ.op[champ.header.prog_size] = '\0';
		vm->champ[i] = champ;
		close(fd);
	}
	return (0);
}
