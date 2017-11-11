int poptGetNextOpt(poptContext con)
{
    const struct poptOption * opt = NULL;
    int done = 0;

    /* looks a bit tricky to get rid of alloca properly in this fn */
#if HAVE_ALLOCA_H
#define ALLOCA(x) alloca(x)
#else
#define ALLOCA(x) malloc(x)
#endif


    while (!done) {
	const char * origOptString = NULL;
	poptCallbackType cb = NULL;
	const void * cbData = NULL;
	const char * longArg = NULL;
	int canstrip = 0;

	while (!con->os->nextCharArg && con->os->next == con->os->argc
		&& con->os > con->optionStack) {
	    cleanOSE(con->os--);
	}
	if (!con->os->nextCharArg && con->os->next == con->os->argc) {
	    invokeCallbacks(con, con->options, 1);
	    if (con->doExec) execCommand(con);
	    return -1;
	}

	/* Process next long option */
	if (!con->os->nextCharArg) {
	    char * localOptString, * optString;
	    int thisopt;

	    if (con->os->argb && PBM_ISSET(con->os->next, con->os->argb)) {
		con->os->next++;
		continue;
	    }
	    thisopt=con->os->next;
	    origOptString = con->os->argv[con->os->next++];

	    if (con->restLeftover || *origOptString != '-') {
		con->leftovers[con->numLeftovers++] = origOptString;
		if (con->flags & POPT_CONTEXT_POSIXMEHARDER)
		    con->restLeftover = 1;
		continue;
	    }

	    /* Make a copy we can hack at */
	    localOptString = optString =
			strcpy(ALLOCA(strlen(origOptString) + 1),
			origOptString);

	    if (!optString[0])
		return POPT_ERROR_BADOPT;

	    if (optString[1] == '-' && !optString[2]) {
		con->restLeftover = 1;
		continue;
	    } else {
		char *oe;
		int singleDash;

		optString++;
		if (*optString == '-')
		    singleDash = 0, optString++;
		else
		    singleDash = 1;

		/* XXX aliases with arg substitution need "--alias=arg" */
		if (handleAlias(con, optString, '\0', NULL))
		    continue;
		if (handleExec(con, optString, '\0'))
		    continue;

		/* Check for "--long=arg" option. */
		for (oe = optString; *oe && *oe != '='; oe++)
		    ;
		if (*oe == '=') {
		    *oe++ = '\0';
		    /* XXX longArg is mapped back to persistent storage. */
		    longArg = origOptString + (oe - localOptString);
		}

		opt = findOption(con->options, optString, '\0', &cb, &cbData,
				 singleDash);
		if (!opt && !singleDash)
		    return POPT_ERROR_BADOPT;
	    }

	    if (!opt) {
		con->os->nextCharArg = origOptString + 1;
	    } else {
		if(con->os == con->optionStack &&
		   opt->argInfo & POPT_ARGFLAG_STRIP) {
		    canstrip = 1;
		    poptStripArg(con, thisopt);
		}
	    }
	}

	/* Process next short option */
	if (con->os->nextCharArg) {
	    origOptString = con->os->nextCharArg;

	    con->os->nextCharArg = NULL;

	    if (handleAlias(con, NULL, *origOptString,
			    origOptString + 1)) {
		origOptString++;
		continue;
	    }
	    if (handleExec(con, NULL, *origOptString))
		continue;

	    opt = findOption(con->options, NULL, *origOptString, &cb,
			     &cbData, 0);
	    if (!opt)
		return POPT_ERROR_BADOPT;

	    origOptString++;
	    if (*origOptString)
		con->os->nextCharArg = origOptString;
	}

	if (opt->arg && (opt->argInfo & POPT_ARG_MASK) == POPT_ARG_NONE) {
	    *((int *)opt->arg) = 1;
	} else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_VAL) {
	    if (opt->arg)
		*((int *) opt->arg) = opt->val;
	} else if ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_NONE) {
	    if (con->os->nextArg) {
		xfree(con->os->nextArg);
		con->os->nextArg = NULL;
	    }
	    if (longArg) {
		con->os->nextArg = expandNextArg(con, longArg);
	    } else if (con->os->nextCharArg) {
		con->os->nextArg = expandNextArg(con, con->os->nextCharArg);
		con->os->nextCharArg = NULL;
	    } else {
		while (con->os->next == con->os->argc &&
		       con->os > con->optionStack) {
		    cleanOSE(con->os--);
		}
		if (con->os->next == con->os->argc)
		    return POPT_ERROR_NOARG;

		/* make sure this isn't part of a short arg or the
                   result of an alias expansion */
		if(con->os == con->optionStack &&
		   opt->argInfo & POPT_ARGFLAG_STRIP &&
		   canstrip) {
		    poptStripArg(con, con->os->next);
		}
		
		con->os->nextArg = expandNextArg(con, con->os->argv[con->os->next++]);
	    }

	    if (opt->arg) {
		long aLong;
		char *end;

		switch (opt->argInfo & POPT_ARG_MASK) {
		  case POPT_ARG_STRING:
		    /* XXX memory leak, hard to plug */
		    *((const char **) opt->arg) = xstrdup(con->os->nextArg);
		    break;

		  case POPT_ARG_INT:
		  case POPT_ARG_LONG:
		    aLong = strtol(con->os->nextArg, &end, 0);
		    if (!(end && *end == '\0'))
			return POPT_ERROR_BADNUMBER;

		    if (aLong == LONG_MIN || aLong == LONG_MAX)
			return POPT_ERROR_OVERFLOW;
		    if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_LONG) {
			*((long *) opt->arg) = aLong;
		    } else {
			if (aLong > INT_MAX || aLong < INT_MIN)
			    return POPT_ERROR_OVERFLOW;
			*((int *) opt->arg) = aLong;
		    }
		    break;

		  default:
		    fprintf(stdout, POPT_("option type (%d) not implemented in popt\n"),
		      opt->argInfo & POPT_ARG_MASK);
		    exit(EXIT_FAILURE);
		}
	    }
	}

	if (cb)
	    cb(con, POPT_CALLBACK_REASON_OPTION, opt, con->os->nextArg, cbData);
	else if (opt->val && ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_VAL))
	    done = 1;

	if ((con->finalArgvCount + 2) >= (con->finalArgvAlloced)) {
	    con->finalArgvAlloced += 10;
	    con->finalArgv = realloc(con->finalArgv,
			    sizeof(*con->finalArgv) * con->finalArgvAlloced);
	}

	{    char *s = malloc((opt->longName ? strlen(opt->longName) : 0) + 3);
	    if (opt->longName)
		sprintf(s, "--%s", opt->longName);
	    else
		sprintf(s, "-%c", opt->shortName);
	    con->finalArgv[con->finalArgvCount++] = s;
	}

	if (opt->arg && (opt->argInfo & POPT_ARG_MASK) != POPT_ARG_NONE
		     && (opt->argInfo & POPT_ARG_MASK) != POPT_ARG_VAL) {
	    con->finalArgv[con->finalArgvCount++] = xstrdup(con->os->nextArg);
	}
    }

    return opt->val;
}