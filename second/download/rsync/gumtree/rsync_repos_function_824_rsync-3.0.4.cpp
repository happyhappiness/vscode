static int handleAlias(/*@special@*/ poptContext con,
		/*@null@*/ const char * longName, char shortName,
		/*@exposed@*/ /*@null@*/ const char * nextCharArg)
	/*@uses con->aliases, con->numAliases, con->optionStack, con->os,
		con->os->currAlias, con->os->currAlias->option.longName @*/
	/*@modifies con @*/
{
    poptItem item = con->os->currAlias;
    int rc;
    int i;

    if (item) {
	if (longName && (item->option.longName &&
		!strcmp(longName, item->option.longName)))
	    return 0;
	if (shortName && shortName == item->option.shortName)
	    return 0;
    }

    if (con->aliases == NULL || con->numAliases <= 0) /* XXX can't happen */
	return 0;

    for (i = con->numAliases - 1; i >= 0; i--) {
	item = con->aliases + i;
	if (longName && !(item->option.longName &&
			!strcmp(longName, item->option.longName)))
	    continue;
	else if (shortName != item->option.shortName)
	    continue;
	break;
    }
    if (i < 0) return 0;

    if ((con->os - con->optionStack + 1) == POPT_OPTION_DEPTH)
	return POPT_ERROR_OPTSTOODEEP;

/*@-boundsread@*/
    if (nextCharArg && *nextCharArg)
	con->os->nextCharArg = nextCharArg;
/*@=boundsread@*/

    con->os++;
    con->os->next = 0;
    con->os->stuffed = 0;
    con->os->nextArg = NULL;
    con->os->nextCharArg = NULL;
    con->os->currAlias = con->aliases + i;
    rc = poptDupArgv(con->os->currAlias->argc, con->os->currAlias->argv,
		&con->os->argc, &con->os->argv);
    con->os->argb = NULL;

    return (rc ? rc : 1);
}