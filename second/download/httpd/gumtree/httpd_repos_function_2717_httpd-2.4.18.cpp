static char *comple(sed_commands_t *commands, sed_comp_args *compargs,
                    char *x1, char *ep, char *x3, char x4)
{
    char *p;

    p = sed_compile(commands, compargs, ep + 1, x3, x4);
    if(p == ep + 1)
        return(ep);
    *ep = compargs->circf;
    return(p);
}