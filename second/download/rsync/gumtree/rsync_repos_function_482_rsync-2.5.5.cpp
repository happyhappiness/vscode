static int handleAlias(poptContext con, const char * longName, char shortName,
		       /*@keep@*/ const char * nextCharArg) {
    int i;

    if (con->os->currAlias && con->os->currAlias->longName && longName &&
	!strcmp(con->os->currAlias->longName, longName))
	return 0;
    if (con->os->currAlias && shortName &&
	    shortName == con->os->currAlias->shortName)
	return 0;

    i = con->numAliases - 1;
    if (longName) {
	while (i >= 0 && (!con->aliases[i].longName ||
	    strcmp(con->aliases[i].longName, longName))) i--;
    } else {
	while (i >= 0 &&
	    con->aliases[i].shortName != shortName) i--;
    }

    if (i < 0) return 0;

    if ((con->os - con->optionStack + 1) == POPT_OPTION_DEPTH)
	return POPT_ERROR_OPTSTOODEEP;

    if (nextCharArg && *nextCharArg)
	con->os->nextCharArg = nextCharArg;

    con->os++;
    con->os->next = 0;
    con->os->stuffed = 0;
    con->os->nextArg = NULL;
    con->os->nextCharArg = NULL;
    con->os->currAlias = con->aliases + i;
    poptDupArgv(con->os->currAlias->argc, con->os->currAlias->argv,
		&con->os->argc, &con->os->argv);
    con->os->argb = NULL;

    return 1;
}