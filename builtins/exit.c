/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:27:47 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/05 11:13:09 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_arg_num(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (1);
	}
	if (ft_atoi(arg) == 0 && ft_strlen(arg) > 2)
		return (1);
	return (0);
}

int	exe_exit(t_parc *node, t_env **env)
{
	t_arg	*arg;
	int		exit_code;

	arg = node->args;
	exit_code = 0;
	printf("exit\n");
	if (arg == NULL)
		exit_code = *env[0]->exit_status;
	else if (if_arg_num(arg->value) == 0)
	{
		if (arg->next == NULL)
			exit_code = ft_atoi(arg->value);
		else
		{
			print_error_msg(node->cmd, NULL, "too many arguments");
			*env[0]->exit_status = 1;
			return (1);
		}
	}
	else
		print_error_msg(node->cmd, arg->value, "numeric argument required");
	freeall(env, &node);
	exit (exit_code);
}
