static int handleExec(/*@special@*/ poptContext con,
		/*@null@*/ const char * longName, char shortName)
	/*@uses con->execs, con->numExecs, con->flags, con->doExec,
		con->finalArgv, con->finalArgvAlloced, con->finalArgvCount @*/
	/*@modifies con @*/
{
    poptItem item;
    int i;

    if (con->execs == NULL || con->numExecs <= 0) /* XXX can't happen */
	return 0;

    for (i = con->numExecs - 1; i >= 0; i--) {
	item = con->execs + i;
	if (longName && !(item->option.longName &&
			!strcmp(longName, item->option.longName)))
	    continue;
	else if (shortName != item->option.shortName)
	    continue;
	break;
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
    if (con->finalArgv != NULL)	/* XXX can't happen */
    {	size_t bufsize = (longName ? strlen(longName) : 0) + 3;
	char *s  = malloc(bufsize);
	if (s != NULL) {	/* XXX can't happen */
	    if (longName)
		snprintf(s, bufsize, "--%s", longName);
	    else
		snprintf(s, bufsize, "-%c", shortName);
	    con->finalArgv[i] = s;
	} else
	    con->finalArgv[i] = NULL;
    }

    /*@-nullstate@*/	/* FIX: con->finalArgv[] == NULL */
    return 1;
    /*@=nullstate@*/
}