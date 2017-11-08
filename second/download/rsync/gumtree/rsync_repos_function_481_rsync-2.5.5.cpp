static int handleExec(poptContext con, char * longName, char shortName) {
    int i;

    i = con->numExecs - 1;
    if (longName) {
	while (i >= 0 && (!con->execs[i].longName ||
	    strcmp(con->execs[i].longName, longName))) i--;
    } else {
	while (i >= 0 &&
	    con->execs[i].shortName != shortName) i--;
    }

    if (i < 0) return 0;

    if (con->flags & POPT_CONTEXT_NO_EXEC)
	return 1;

    if (con->doExec == NULL) {
	con->doExec = con->execs + i;
	return 1;
    }

    /* We already have an exec to do; remember this option for next
       time 'round */
    if ((con->finalArgvCount + 1) >= (con->finalArgvAlloced)) {
	con->finalArgvAlloced += 10;
	con->finalArgv = realloc(con->finalArgv,
			sizeof(*con->finalArgv) * con->finalArgvAlloced);
    }

    i = con->finalArgvCount++;
    {	char *s  = malloc((longName ? strlen(longName) : 0) + 3);
	if (longName)
	    sprintf(s, "--%s", longName);
	else
	    sprintf(s, "-%c", shortName);
	con->finalArgv[i] = s;
    }

    return 1;
}