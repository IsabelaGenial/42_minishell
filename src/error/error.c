#include "shell.h"

void *my_error(int err_type,char *input,int erro)
{
    g_main.status = erro;
    if(err_type == QUOTE)
        ft_putstr_fd("Error: unclosed quotes\n", 2);
}