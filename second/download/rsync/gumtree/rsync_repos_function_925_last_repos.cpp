const char * poptBadOption(poptContext con, int flags)
{
    struct optionStackEntry * os = NULL;

    if (con != NULL)
	os = (flags & POPT_BADOPTION_NOALIAS) ? con->optionStack : con->os;

    /*@-nullderef@*/	/* LCL: os->argv != NULL */
    return (os && os->argv ? os->argv[os->next - 1] : NULL);
    /*@=nullderef@*/
}