SHELL = /bin/sh

NAME_FILE = ../asm

LIB_PRINTF = ../ft_printf/libftprintf.a
LIB_PRINTF_NAME = -lftprintf
LIB_PRINTF_PATH = ../ft_printf/
LIB_PRINTF_INCL = ../ft_printf/includes/

LIBFT_NAME = -lft
LIB_PATH = ../libft/

SRCS = asm.c command_check.c command_length.c ft_isdigitalword.c ft_isspecial.c ft_skipword.c  if_checks.c \
	init_headers.c label_substitution.c print_comands.c print_header.c rewind.c tkn_str_cat.c tokens_lst.c tokenizer.c \
	token_sequence_check.c token_fill.c token_exception.c ft_wordequ.c fast_strsplit.c

HEADER_PATH = ./
HEADER_PATH_OP = ../
HEADERS_ASM = asm.h errors.h libword.h op.h options.h

OBJS = $(SRCS:.c=.o)

# For libftprintf
export SRC_FILES_GEN = field_len.c fill_union.c ft_itoa_base_printf.c ft_printf.c get_binary.c is_parser.c is_typeflags.c \
	make_field.c parsing_funcs.c parsing_generaly.c prepare_lennum.c set_buff.c set_flags.c str_tolower.c \
	to_buff.c which_sign.c zeroing.c

export SRC_FILES_FLOAT = check_create_float_res.c e_flag_intf.c float_intf.c float_rounding.c frees_for_float.c ft_log10.c \
	ft_log2.c g_flag_intf.c get_dbl_values.c get_ldbl_values.c high_precision.c high_precision_intf.c \
	high_precision_intf_long.c high_precision_long.c my_float.c my_long_float.c print_reserve_dbl.c

export HEADERS_NAME = ft_ptintf.h high_precision.h my_float.h

PREREQUISITE_FT_PRINTF = $(SRC_FILES_GEN) $(SRC_FILES_FLOAT) $(HEADERS_NAME)

# For libft
export SRCS_LIBFT = ft_strlen.c ft_strcmp.c ft_strncmp.c ft_strcpy.c ft_strncpy.c \
	ft_strcat.c ft_strncat.c ft_strlcat.c ft_strstr.c ft_strnstr.c \
	ft_strchr.c ft_strrchr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_toupper.c ft_isupper.c ft_islower.c \
	ft_tolower.c ft_strdup.c ft_atoi.c ft_memset.c ft_bzero.c ft_memcpy.c \
	ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c \
	ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
	ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
	ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
	ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
	ft_lstadd.c ft_lstiter.c ft_lstpush.c ft_pow.c ft_fib.c ft_sqrt.c \
	ft_isspace.c ft_is_complex_string.c ft_lstcirc_add.c ft_lstcirc_delelem.c \
	ft_lstcirc_findcontent_size.c ft_strjoinre.c ft_strndup.c \
	ft_lstcirc_strnew.c ft_strlcpy.c ft_sstrchr.c ft_floor.c ft_abs.c \
	ft_reverse.c get_next_line.c \
	ml_strdup.c ml_memalloc.c ml_strnew.c ml_strmap.c ml_strmapi.c ml_strsub.c \
	ml_strjoin.c ml_strtrim.c ml_strsplit.c ml_itoa.c ml_strjoinre.c \
	ml_strndup.c ml_get_next_line.c go_exit.c

export SRC_ML = ml_create.c ml_del.c ml_general.c memlist_bottleneck.c ml_givemem.c

HEADERS_LIBFT = get_next_line.h libft.h memlist.h blackbox_memlist.h

export PREREQUISITE_LIBFT = $(SRCS_LIBFT) $(SRC_ML) $(HEADERS_LIBFT)

vpath %.c ../ ../ft_printf/srcs ../ft_printf/srcsFloat ../libft ../libft/memlist
vpath %.h ./includes/ ../ ../ft_printf/includes ../libft ../libft/memlist

.PHONY: clean fclean re
all: $(NAME_FILE)

$(NAME_FILE): $(LIB_PRINTF) $(OBJS)
	gcc -o $(NAME_FILE) $(OBJS) -L$(LIB_PATH) $(LIBFT_NAME) -L$(LIB_PRINTF_PATH) $(LIB_PRINTF_NAME)

$(LIB_PRINTF): $(PREREQUISITE_FT_PRINTF) $(PREREQUISITE_LIBFT)
	$(MAKE) -C $(LIB_PRINTF_PATH)

$(OBJS): %.o:%.c $(HEADERS)
	@gcc -c $< -I$(HEADER_PATH) -I$(HEADER_PATH_OP) -I$(LIB_PATH) -I$(LIB_PRINTF_INCL) $(CFLAGS) -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIB_PRINTF_PATH) clean

fclean: clean
	@rm -f $(NAME_FILE)
	@$(MAKE) -C $(LIB_PRINTF_PATH) fclean

re: fclean all
