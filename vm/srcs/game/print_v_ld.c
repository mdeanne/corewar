/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_v_ld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 13:55:04 by ylila             #+#    #+#             */
/*   Updated: 2020/05/17 13:55:53 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_v_4_ld(t_corewar *corewar, t_parse_args *arg_val,
														const char *cmd)
{
	int		val;

	val = get_value_frm_arg(arg_val, 0, corewar, 1);
	ft_printf("P %4d | %s %d r%d\n",
			corewar->carriages->id,
			cmd,
			val,
			arg_val->val[1]);
}

void		print_v_4_ldi(t_corewar *corewar, t_parse_args *arg_val,
															const char *cmd)
{
	int		val_addr_1;
	int		val_addr_2;

	if (arg_val->code_args[0] == DIR_CODE)
		val_addr_1 = (int16_t)get_value_frm_arg(arg_val, 0, corewar, 1);
	else
		val_addr_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	if (arg_val->code_args[1] == DIR_CODE)
		val_addr_2 = (int16_t)get_value_frm_arg(arg_val, 1, corewar, 1);
	else
		val_addr_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	ft_printf("P %4d | %s %d %d r%d\n"
		"       | -> load from %d + %d = %d (with pc and mod %ld)\n",
	corewar->carriages->id, cmd, val_addr_1, val_addr_2, arg_val->val[2],
	val_addr_1, val_addr_2, val_addr_1 + val_addr_2,
	((val_addr_1 + val_addr_2) % IDX_MOD < 0 && corewar->carriages->op_pos +
		(val_addr_1 + val_addr_2) % IDX_MOD < corewar->arena)
		? do_steps(corewar->carriages->op_pos, (val_addr_1 + val_addr_2)
		% IDX_MOD, corewar->arena) - corewar->arena - MEM_SIZE
		: do_steps(corewar->carriages->op_pos, (val_addr_1 + val_addr_2)
		% IDX_MOD, corewar->arena) - corewar->arena);
}

void		print_v_4_lld(t_corewar *corewar, t_parse_args *arg_val,
					const char *cmd)
{
	int		val;

	val = get_value_frm_arg(arg_val, 0, corewar, 0);
	ft_printf("P %4d | %s %d r%d\n",
	corewar->carriages->id, cmd, val, arg_val->val[1]);
}

void		print_v_4_lldi(t_corewar *corewar, t_parse_args *arg_val,
														const char *cmd)
{
	int		val_addr_1;
	int		val_addr_2;

	if (arg_val->code_args[0] == DIR_CODE)
		val_addr_1 = (int16_t)get_value_frm_arg(arg_val, 0, corewar, 1);
	else
		val_addr_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	if (arg_val->code_args[1] == DIR_CODE)
		val_addr_2 = (int16_t)get_value_frm_arg(arg_val, 1, corewar, 0);
	else
		val_addr_2 = get_value_frm_arg(arg_val, 1, corewar, 0);
	ft_printf("P %4d | %s %d %d r%d\n"
		"       | -> load from %d + %d = %d (with pc %ld)\n",
		corewar->carriages->id, cmd, val_addr_1, val_addr_2, arg_val->val[2],
		val_addr_1, val_addr_2, val_addr_1 + val_addr_2,
		(val_addr_1 + val_addr_2 < 0 && corewar->carriages->op_pos +
		(val_addr_1 + val_addr_2) < corewar->arena)
		? do_steps(corewar->carriages->op_pos, (val_addr_1 + val_addr_2),
		corewar->arena) - corewar->arena - MEM_SIZE
		: do_steps(corewar->carriages->op_pos, (val_addr_1 + val_addr_2),
		corewar->arena) - corewar->arena);
}
