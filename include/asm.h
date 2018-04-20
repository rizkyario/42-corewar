/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:00:50 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/15 12:02:48 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

# define SOURCEFILE		1
# define EMPTY			2
# define NEWLINE		3
# define MALLOC			4
# define HEADER			5
# define NAME_LEN		6
# define COMMENT_LEN	8
# define OP				9

typedef struct	s_param
{
	char		*str;
	int			type;
	int			size;
	int			value;
}				t_param;

typedef struct	s_op
{
	char		*opname;
	int			opcode;
	int			size;
	t_param		params[3];
	int			param_c;
	char		*func;
	int			offset;
}				t_op;

typedef struct	s_asm
{
	int			i;
	char		*name;
	char		*comment;
	char		**file;
	char		**labels;
	t_op		ops[1000];
	int			op_c;
	int			size;
}				t_asm;

int				ft_parsing(t_asm *a, header_t *h);
int				ft_get_name(t_asm *a, header_t *h);
int				ft_get_comment(t_asm *a, header_t *h);
int				ft_check_instructions(t_asm *a);
int				ft_get_op(t_asm *a);
int				ft_error(int errcode, int status);

int				ft_file_is_empty(char *file);
int				ft_line_is_empty(t_asm *a);
void			ft_skip_empty_lines(t_asm *a);
void			ft_handle_comments(char **file);
void			ft_trim_file(char **file);
void			ft_print_tab(char **tab);
int				ft_free(char *str, int status);
int				ft_free_tab(char **tab, int status);

void			asm_print(t_asm *a);

char			*ft_strcdup(const char *s1, const char c);

#endif