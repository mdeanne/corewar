#include "vm.h"

void    live(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	t_carriages	*carrig;

	if (!*head)
	    return ;
	carrig = corewar->carriages;
	while (carrig)
	{
		if (carrig->is_live && -carrig->reg[0] == arg_val->val[0])
		{
			corewar->game_param.who_lst_live = arg_val->val[0];
			break ;
		}
		carrig = carrig->next;
	}
	++corewar->game_param.live_period_cnt;
	corewar->carriages->cycle_when_live = corewar->game_param.cycles_aft_start;
}

void    ld(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
    int					val;

    if (!*head)
        return ;
    val = get_value_frm_arg(arg_val, 0, corewar, 1);
    corewar->carriages->reg[arg_val->val[1] - 1] = val;
    if (!val)
        corewar->carriages->carry = 1;
    else
        corewar->carriages->carry = 0;
}

void    ldi(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int					val_addr_1;
	int					val_addr_2;

	if (!*head)
		return ;
	val_addr_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_addr_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	corewar->carriages->reg[arg_val->val[2] - 1] = reverse_vm_int_bytes(
			(unsigned int *)do_steps(corewar->carriages->op_pos,
					(val_addr_1 + val_addr_2) % IDX_MOD, corewar->arena));
}

void    lld(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int					val;

	if (!*head)
		return ;
	val = get_value_frm_arg(arg_val, 0, corewar, 0);
	corewar->carriages->reg[arg_val->val[1] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void    lldi(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int					val_addr_1;
	int					val_addr_2;

	if (!*head)
		return ;
	val_addr_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_addr_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	corewar->carriages->reg[arg_val->val[2] - 1] = reverse_vm_int_bytes(
			(unsigned int *)do_steps(corewar->carriages->op_pos,
					(val_addr_1 + val_addr_2), corewar->arena));
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	st(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val;
	unsigned char	*ind_pos;
	int				i;
	unsigned char	*val_ptr;

	if (!*head)
		return ;
	val = corewar->carriages->reg[arg_val->code_args[0] - 1];
	if (arg_val->code_args[1] == REG_CODE)
		corewar->carriages->reg[arg_val->code_args[1] - 1] = val;
	else if (arg_val->code_args[1] == IND_CODE)
	{
		ind_pos = do_steps(corewar->carriages->op_pos,
				arg_val->val[1] % IDX_MOD, corewar->arena);
		i = 4;
		val_ptr = (unsigned char *)&val;
		while (--i >= 0)
			*ind_pos++ = *(val_ptr + i);
	}
}

void	sti(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	unsigned char	*ind_pos;
	int				val_addr_1;
	int				val_addr_2;
	int				i;
	unsigned char	*val_ptr;

	if (!*head)
		return ;
	val_addr_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_addr_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	ind_pos = do_steps(corewar->carriages->op_pos,
			(val_addr_1 + val_addr_2) % IDX_MOD, corewar->arena);
	i = 4;
	val_ptr = (unsigned char *)&corewar->carriages->reg[arg_val->val[0] - 1];
	while (--i >= 0)
		*ind_pos++ = *(val_ptr + i);
}

void	zjump(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	if (!corewar->carriages->carry || !*head)
		return ;
	corewar->carriages->op_pos = do_steps(corewar->carriages->op_pos,
			arg_val->val[0] % IDX_MOD, corewar->arena);
}

void	add(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val;

	if (!*head)
		return ;
	val = corewar->carriages->reg[arg_val->val[0] - 1] +
			corewar->carriages->reg[arg_val->val[1] - 1];
	corewar->carriages->reg[arg_val->val[2] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	sub(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val;

	if (!*head)
		return ;
	val = corewar->carriages->reg[arg_val->val[0] - 1] -
		  corewar->carriages->reg[arg_val->val[1] - 1];
	corewar->carriages->reg[arg_val->val[2] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	and(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val_1;
	int				val_2;

	if (!*head)
		return ;
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 & val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	or(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val_1;
	int				val_2;

	if (!*head)
		return ;
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 | val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	xor(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val_1;
	int				val_2;

	if (!*head)
		return ;
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 ^ val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	aff(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	if (!*head || !(corewar->flgs.flgs & A_FLG))
		return ;
	ft_printf("%c\n",
			(char)corewar->carriages->reg[arg_val->val[0] - 1]);
}

void	nfork(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	push_front_carriage(head);
	(*head)->carry = corewar->carriages->carry;
	(*head)->cycle_when_live = corewar->carriages->cycle_when_live;
	ft_memcpy((*head)->reg, corewar->carriages->reg,
			sizeof(corewar->carriages->reg));
	(*head)->op_pos = do_steps(corewar->carriages->op_pos,
			arg_val->val[0] % IDX_MOD, corewar->arena);
}

void	lfork(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	push_front_carriage(head);
	(*head)->carry = corewar->carriages->carry;
	(*head)->cycle_when_live = corewar->carriages->cycle_when_live;
	ft_memcpy((*head)->reg, corewar->carriages->reg,
			  sizeof(corewar->carriages->reg));
	(*head)->op_pos = do_steps(corewar->carriages->op_pos,
			arg_val->val[0], corewar->arena);
}