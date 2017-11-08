void poptFreeContext(poptContext con) {
    int i;

    poptResetContext(con);
    if (con->os->argb) free(con->os->argb);

    for (i = 0; i < con->numAliases; i++) {
	if (con->aliases[i].longName) xfree(con->aliases[i].longName);
	free(con->aliases[i].argv);
    }

    for (i = 0; i < con->numExecs; i++) {
	if (con->execs[i].longName) xfree(con->execs[i].longName);
	xfree(con->execs[i].script);
    }
    if (con->execs) xfree(con->execs);

    free(con->leftovers);
    free(con->finalArgv);
    if (con->appName) xfree(con->appName);
    if (con->aliases) free(con->aliases);
    if (con->otherHelp) xfree(con->otherHelp);
    if (con->execPath) xfree(con->execPath);
    if (con->arg_strip) PBM_FREE(con->arg_strip);
    
    free(con);
}