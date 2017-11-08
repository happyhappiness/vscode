void poptResetContext(poptContext con) {
    int i;

    while (con->os > con->optionStack) {
	cleanOSE(con->os--);
    }
    if (con->os->argb) {
	PBM_FREE(con->os->argb);
	con->os->argb = NULL;
    }
    con->os->currAlias = NULL;
    con->os->nextCharArg = NULL;
    con->os->nextArg = NULL;
    con->os->next = 1;			/* skip argv[0] */

    con->numLeftovers = 0;
    con->nextLeftover = 0;
    con->restLeftover = 0;
    con->doExec = NULL;

    for (i = 0; i < con->finalArgvCount; i++) {
	if (con->finalArgv[i]) {
	    xfree(con->finalArgv[i]);
	    con->finalArgv[i] = NULL;
	}
    }

    con->finalArgvCount = 0;

    if (con->arg_strip) {
	PBM_FREE(con->arg_strip);
	con->arg_strip = NULL;
    }
}