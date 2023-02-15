/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:45:17 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/15 11:16:50 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //printf
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"
# include <stdlib.h> //free

enum e_token
{
	word = 144,
	redirect = 22,
	piper = 89
};

typedef struct s_cell
{
	char			*content;
	enum e_token	token;
	struct s_cell	*next;
}	t_cell;

typedef struct s_info
{
	char	*prompt;
	char	**sentence;
	int		qtd_sentence;

}	t_info;

typedef struct s_sentence
{
	int					input;
	char				*command;
	char				*args;// Tem que ser ** por causa do exeqv.
	int					output;
	struct s_sentence	*next;
}	t_sentence;

void	divide_prompt(t_info *info, t_cell **list_cells);
void	create_new_cell(t_cell **list_cells, char *str);
void	categorize_elements(t_cell **list);
void	list_clear_cells(t_cell **list);

//Signal
void	check_eof(t_info *info);
void	set_signal_handler(void);

// main
void	expand_variable(t_cell **list_cell, t_info info);
void	golfer(t_sentence *sent, t_info *info);

#endif
