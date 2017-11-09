void poptResetContext(poptContext con)
{
    int i;

    if (con == NULL) return;
    while (con->os > con->optionStack) {
	cleanOSE(con->os--);
    }
    con->os->argb = PBM_FREE(con->os->argb);
    con->os->currAlias = NULL;
    con->os->nextCharArg = NULL;
    con->os->nextArg = NULL;
    con->os->next = 1;			/* skip argv[0] */

    con->numLeftovers = 0;
    con->nextLeftover = 0;
    con->restLeftover = 0;
    con->doExec = NULL;

    if (con->finalArgv != NULL)
    for (i = 0; i < con->finalArgvCount; i++) {
	/*@-unqualifiedtrans@*/		/* FIX: typedef double indirection. */
	con->finalArgv[i] = _free(con->finalArgv[i]);
	/*@=unqualifiedtrans@*/
    }

    con->finalArgvCount = 0;
    con->arg_strip = PBM_FREE(con->arg_strip);
    /*@-nullstate@*/	/* FIX: con->finalArgv != NULL */
    return;
    /*@=nullstate@*/
}