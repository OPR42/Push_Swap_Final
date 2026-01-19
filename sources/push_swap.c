/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:13:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/09 16:13:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	parse_flags(t_data *data, char *arg, int algo)
{
	short	b;

	b = data->bench_mode;
	if (ps_strncmp(arg, "--adaptive", 10) == 0 && (algo == 0 || algo == 5))
		data->algo_type = 5;
	else if (ps_strncmp(arg, "--simple", 8) == 0 && (algo == 0 || algo == 1))
		data->algo_type = 1;
	else if (ps_strncmp(arg, "--medium", 8) == 0 && (algo == 0 || algo == 2))
		data->algo_type = 2;
	else if (ps_strncmp(arg, "--complex", 9) == 0 && (algo == 0 || algo == 3))
		data->algo_type = 3;
	else if (ps_strncmp(arg, "--custom", 8) == 0 && (algo == 0 || algo == 4))
		data->algo_type = 4;
	else if (ps_strncmp(arg, "--bench", 8) == 0 && b != 2 && b != 3)
		data->bench_mode = 1;
	else if (ps_strncmp(arg, "--benchview", 12) == 0 && b != 1 && b != 3)
		data->bench_mode = 2;
	else if (ps_strncmp(arg, "--benchanim", 12) == 0 && b != 1 && b != 2)
		data->bench_mode = 3;
	else
		return (-1);
	return (0);
}

static int	parse_args(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (ps_isint(argv[i]) == 1)
		{
			if (send_nodes(data, (int)ps_atolli(argv[i])) == -1)
				return (-1);
		}
		else if (ps_strncmp(argv[i], "--", 2) == 0)
		{
			if (parse_flags(data, argv[i], data->algo_type) != 0)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	return (0);
}

static int	split_args(t_data *data, int argc, char **argv)
{
	int		i;
	int		subargc;
	char	**subargv;

	i = 1;
	while (i < argc)
	{
		subargv = ps_split(argv[i], ' ');
		if (subargv == NULL)
			return (ps_free_all(subargv, subargc), -1);
		subargc = 0;
		while (subargv[subargc])
			subargc++;
		if (subargc < 1 || parse_args(data, subargc, subargv) == -1)
			return (ps_free_all(subargv, subargc), -1);
		ps_free_all(subargv, subargc);
		i++;
	}
	if (data->count_nb < 2)
		return (-1);
	ps_set_ranks(data, 0, 0);
	data->stack_a_curr->next = data->stack_a_hook;
	data->stack_a_hook->previous = data->stack_a_curr;
	return (0);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\033[2J\033[?25h\033[H", 13);
	write(1, "\n  \033[0;91m╔═══════════════════════════════════════════", 143);
	write(1, "══════════════╗\n  ║         \033[0m✋🛑 Program \033[0;95m", 88);
	write(1, "Push_Swap\033[0m interrupted 🛑✋\033[0;91m         ║\n", 54);
	write(1, "  ╚══════════════════════════════════════════════════", 156);
	write(1, "═══════╝\033[0m\n\n", 31);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data				data;
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, 0);
	if (argc == 1)
		return (0);
	if (init_data(&data) == -1 || split_args(&data, argc, argv) == -1)
	{
		ps_stack_clear((t_stack *)data.stack_a_hook);
		ps_stack_clear((t_stack *)data.stack_b_hook);
		write(1, "\033[2J\033[?25l\033[?25h\033[0m", 20);
		write(2, "Error\n", 6);
		return (-1);
	}
	ps_algochoice(&data);
	write(1, "\033[?25h", 6);
	free(data.algo_name);
	free(data.algo_class);
	ps_stack_clear((t_stack *)data.stack_a_hook);
	ps_stack_clear((t_stack *)data.stack_b_hook);
	return (0);
}
