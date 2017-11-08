static void poptStripArg(/*@special@*/ poptContext con, int which)
	/*@uses con->arg_strip, con->optionStack @*/
	/*@defines con->arg_strip @*/
	/*@modifies con @*/
{
    /*@-sizeoftype@*/
    if (con->arg_strip == NULL)
	con->arg_strip = PBM_ALLOC(con->optionStack[0].argc);
    if (con->arg_strip != NULL)		/* XXX can't happen */
    PBM_SET(which, con->arg_strip);
    /*@=sizeoftype@*/
    /*@-compdef@*/ /* LCL: con->arg_strip udefined? */
    return;
    /*@=compdef@*/
}