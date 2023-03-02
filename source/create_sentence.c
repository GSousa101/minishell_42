/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sentence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:18:42 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/02 18:26:00 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_sentences(t_cell *list)
{
	int	len;

	len = 1;
	while (list)
	{
		if (list->token == piper)
			len++;
		list = list->next;
	}
	return (len);
}

/*
 * Tenho que fechar o fd anterior do output ou input(se nao for o padrao 0 e 1).
 * Cro um fd novo (com open), criando o arquivo.
 * A flag do open vai depende do tipo de seta.
 * E tratar error se o open falhar (retorno -1, e o errno diz qual foi)
 * Coloco o fd como output(> ou >>) ou input(<) daquela sentença.
void	open_redirect()
{
	
}
 */

t_cell	*new_sent(t_cell *list_in, t_list_sent **list_sentence)
{
	int			n_round;
	t_sentence	sent_node;

	n_round = 0;
	while (list_in && list_in->token != piper)
	{
		if (list_in->token == redirect)
		{
			//open_redirect();
			list_in = list_in->next;
		}
		else if (n_round == 0)
			sent_node.command = ft_strdup(list_in->content);
		else if (n_round == 1)
			sent_node.args = ft_strdup(list_in->content);
		else
		{
			if (list_in->space == 1)
				sent_node.args = ft_strjoin_free(sent_node.args, " ");
			sent_node.args = ft_strjoin_free(sent_node.args, list_in->content);
		}
		n_round++;
		list_in = list_in->next;
		if (!list_in)
			break ;
	}
	ft_lstadd_back_sent(list_sentence, ft_lstnew_sent(sent_node));
	return (list_in);
}

/*
 * Criar a sentença para enviar para os comandos.
 */
// Fazer aqui o redirect.
// e Heredoc
t_list_sent	*create_sentence(t_cell *list_in, t_info *info)
{
	int			i;
	t_list_sent	*sent;

	sent = NULL;
	info->qtd_sent = count_sentences(list_in);
	i = 0;
	while (i < info->qtd_sent)
	{
		list_in = new_sent(list_in, &sent);
		if (list_in == NULL)
			break ;
		i++;
		list_in = list_in->next;
	}
	return (sent);
}
