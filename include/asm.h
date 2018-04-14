/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:00:50 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/14 11:16:41 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

# define NAME			1
# define NAME_LEN		2
# define COMMENT		3
# define COMMENT_LEN	4
# define OP				5

# define PTYPE_REG 0
# define PTYPE_IND 1
# define PTYPE_DIR 2

typedef struct	s_param
{
	char		*str;
	int			type;
	int			size;
	int			value;
}				t_param;

typedef struct	s_op
{
	int			opcode;
	int			size;
	t_param		params[3];
	int			param_counter;
	int			offset;
}				t_op;

typedef struct	s_asm
{
	int			i;
	char		*name;
	char		*comment;
	char		**file;
	t_op		ops[1000];
	int			op_counter;
}				t_asm;

int				ft_parsing(t_asm *a, header_t *h);
int				ft_get_name(t_asm *a, header_t *h);
int				ft_get_comment(t_asm *a, header_t *h);
int				ft_get_op(t_asm *a, header_t *h);
int				ft_error(int errcode, int status);

void			ft_handle_comments(char **file);
int				ft_line_is_empty(t_asm *a);
void			ft_skip_empty_lines(t_asm *a);
void			ft_trim_file(char **file);
void			ft_print_tab(char **tab);
int				ft_free_tab(char **tab, int status);

#endif
