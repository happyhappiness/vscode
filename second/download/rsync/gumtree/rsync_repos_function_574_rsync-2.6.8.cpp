int poptGetNextOpt(poptContext con)
{
    const struct poptOption * opt = NULL;
    int done = 0;

    if (con == NULL)
	return -1;
    while (!done) {
	const char * origOptString = NULL;
	poptCallbackType cb = NULL;
	const void * cbData = NULL;
	const char * longArg = NULL;
	int canstrip = 0;
	int shorty = 0;

	while (!con->os->nextCharArg && con->os->next == con->os->argc
		&& con->os > con->optionStack) {
	    cleanOSE(con->os--);
	}
	if (!con->os->nextCharArg && con->os->next == con->os->argc) {
	    /*@-internalglobs@*/
	    invokeCallbacksPOST(con, con->options);
	    /*@=internalglobs@*/
	    if (con->doExec) return execCommand(con);
	    return -1;
	}

	/* Process next long option */
	if (!con->os->nextCharArg) {
	    char * localOptString, * optString;
	    int thisopt;

	    /*@-sizeoftype@*/
	    if (con->os->argb && PBM_ISSET(con->os->next, con->os->argb)) {
		con->os->next++;
		continue;
	    }
	    /*@=sizeoftype@*/
	    thisopt = con->os->next;
	    if (con->os->argv != NULL)	/* XXX can't happen */
	    origOptString = con->os->argv[con->os->next++];

	    if (origOptString == NULL)	/* XXX can't happen */
		return POPT_ERROR_BADOPT;

	    if (con->restLeftover || *origOptString != '-') {
		if (con->flags & POPT_CONTEXT_POSIXMEHARDER)
		    con->restLeftover = 1;
		if (con->flags & POPT_CONTEXT_ARG_OPTS) {
		    con->os->nextArg = xstrdup(origOptString);
		    return 0;
		}
		if (con->leftovers != NULL)	/* XXX can't happen */
		    con->leftovers[con->numLeftovers++] = origOptString;
		continue;
	    }

	    /* Make a copy we can hack at */
	    localOptString = optString =
		strcpy(alloca(strlen(origOptString) + 1), origOptString);

	    if (optString[0] == '\0')
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
		    {};
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
		if (con->os == con->optionStack &&
		   opt->argInfo & POPT_ARGFLAG_STRIP)
		{
		    canstrip = 1;
		    poptStripArg(con, thisopt);
		}
		shorty = 0;
	    }
	}

	/* Process next short option */
	/*@-branchstate@*/		/* FIX: W2DO? */
	if (con->os->nextCharArg) {
	    origOptString = con->os->nextCharArg;

	    con->os->nextCharArg = NULL;

	    if (handleAlias(con, NULL, *origOptString, origOptString + 1))
		continue;

	    if (handleExec(con, NULL, *origOptString)) {
		/* Restore rest of short options for further processing */
		origOptString++;
		if (*origOptString != '\0')
		    con->os->nextCharArg = origOptString;
		continue;
	    }

	    opt = findOption(con->options, NULL, *origOptString, &cb,
			     &cbData, 0);
	    if (!opt)
		return POPT_ERROR_BADOPT;
	    shorty = 1;

	    origOptString++;
	    if (*origOptString != '\0')
		con->os->nextCharArg = origOptString;
	}
	/*@=branchstate@*/

	if (opt == NULL) return POPT_ERROR_BADOPT;	/* XXX can't happen */
	if (opt->arg && (opt->argInfo & POPT_ARG_MASK) == POPT_ARG_NONE) {
	    if (poptSaveInt(opt, 1L))
		return POPT_ERROR_BADOPERATION;
	} else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_VAL) {
	    if (opt->arg) {
		if (poptSaveInt(opt, (long)opt->val))
		    return POPT_ERROR_BADOPERATION;
	    }
	} else if ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_NONE) {
	    con->os->nextArg = _free(con->os->nextArg);
	    /*@-usedef@*/	/* FIX: W2DO? */
	    if (longArg) {
	    /*@=usedef@*/
		longArg = expandNextArg(con, longArg);
		con->os->nextArg = longArg;
	    } else if (con->os->nextCharArg) {
		longArg = expandNextArg(con, con->os->nextCharArg);
		con->os->nextArg = longArg;
		con->os->nextCharArg = NULL;
	    } else {
		while (con->os->next == con->os->argc &&
		       con->os > con->optionStack) {
		    cleanOSE(con->os--);
		}
		if (con->os->next == con->os->argc) {
		    if (!(opt->argInfo & POPT_ARGFLAG_OPTIONAL))
			/*@-compdef@*/	/* FIX: con->os->argv not defined */
			return POPT_ERROR_NOARG;
			/*@=compdef@*/
		    con->os->nextArg = NULL;
		} else {

		    /*
		     * Make sure this isn't part of a short arg or the
		     * result of an alias expansion.
		     */
		    if (con->os == con->optionStack &&
			(opt->argInfo & POPT_ARGFLAG_STRIP) &&
			canstrip) {
			poptStripArg(con, con->os->next);
		    }
		
		    if (con->os->argv != NULL) {	/* XXX can't happen */
			/* XXX watchout: subtle side-effects live here. */
			longArg = con->os->argv[con->os->next++];
			longArg = expandNextArg(con, longArg);
			con->os->nextArg = longArg;
		    }
		}
	    }
	    longArg = NULL;

	    if (opt->arg) {
		switch (opt->argInfo & POPT_ARG_MASK) {
		case POPT_ARG_STRING:
		    /* XXX memory leak, hard to plug */
		    *((const char **) opt->arg) = (con->os->nextArg)
			? xstrdup(con->os->nextArg) : NULL;
		    /*@switchbreak@*/ break;

		case POPT_ARG_INT:
		case POPT_ARG_LONG:
		{   long aLong = 0;
		    char *end;

		    if (con->os->nextArg) {
			aLong = strtol(con->os->nextArg, &end, 0);
			if (!(end && *end == '\0'))
			    return POPT_ERROR_BADNUMBER;
		    }

		    if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_LONG) {
			if (aLong == LONG_MIN || aLong == LONG_MAX)
			    return POPT_ERROR_OVERFLOW;
			if (poptSaveLong(opt, aLong))
			    return POPT_ERROR_BADOPERATION;
		    } else {
			if (aLong > INT_MAX || aLong < INT_MIN)
			    return POPT_ERROR_OVERFLOW;
			if (poptSaveInt(opt, aLong))
			    return POPT_ERROR_BADOPERATION;
		    }
		}   /*@switchbreak@*/ break;

		case POPT_ARG_FLOAT:
		case POPT_ARG_DOUBLE:
		{   double aDouble = 0.0;
		    char *end;

		    if (con->os->nextArg) {
			/*@-mods@*/
			int saveerrno = errno;
			errno = 0;
			aDouble = strtod(con->os->nextArg, &end);
			if (errno == ERANGE)
			    return POPT_ERROR_OVERFLOW;
			errno = saveerrno;
			/*@=mods@*/
			if (*end != '\0')
			    return POPT_ERROR_BADNUMBER;
		    }

		    if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_DOUBLE) {
			*((double *) opt->arg) = aDouble;
		    } else {
#ifndef DBL_EPSILON
#define DBL_EPSILON 2.2204460492503131e-16
#endif
#define MY_ABS(a) ((((a) - 0.0) < DBL_EPSILON) ? -(a) : (a))
			if ((MY_ABS(aDouble) - FLT_MAX) > DBL_EPSILON)
			    return POPT_ERROR_OVERFLOW;
			if ((FLT_MIN - MY_ABS(aDouble)) > DBL_EPSILON)
			    return POPT_ERROR_OVERFLOW;
			*((float *) opt->arg) = aDouble;
		    }
		}   /*@switchbreak@*/ break;
		default:
		    fprintf(stdout,
			POPT_("option type (%d) not implemented in popt\n"),
			(opt->argInfo & POPT_ARG_MASK));
		    exit(EXIT_FAILURE);
		    /*@notreached@*/ /*@switchbreak@*/ break;
		}
	    }
	}

	if (cb) {
	    /*@-internalglobs@*/
	    invokeCallbacksOPTION(con, con->options, opt, cbData, shorty);
	    /*@=internalglobs@*/
	} else if (opt->val && ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_VAL))
	    done = 1;

	if ((con->finalArgvCount + 2) >= (con->finalArgvAlloced)) {
	    con->finalArgvAlloced += 10;
	    con->finalArgv = realloc(con->finalArgv,
			    sizeof(*con->finalArgv) * con->finalArgvAlloced);
	}

	if (con->finalArgv != NULL)
	{   char *s = malloc((opt->longName ? strlen(opt->longName) : 0) + 3);
	    if (s != NULL) {	/* XXX can't happen */
		if (opt->longName)
		    sprintf(s, "%s%s",
			((opt->argInfo & POPT_ARGFLAG_ONEDASH) ? "-" : "--"),
			opt->longName);
		else
		    sprintf(s, "-%c", opt->shortName);
		con->finalArgv[con->finalArgvCount++] = s;
	    } else
		con->finalArgv[con->finalArgvCount++] = NULL;
	}

	if (opt->arg && (opt->argInfo & POPT_ARG_MASK) == POPT_ARG_NONE)
	    /*@-ifempty@*/ ; /*@=ifempty@*/
	else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_VAL)
	    /*@-ifempty@*/ ; /*@=ifempty@*/
	else if ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_NONE) {
	    if (con->finalArgv != NULL && con->os->nextArg)
	        con->finalArgv[con->finalArgvCount++] =
			/*@-nullpass@*/	/* LCL: con->os->nextArg != NULL */
			xstrdup(con->os->nextArg);
			/*@=nullpass@*/
	}
    }

    return (opt ? opt->val : -1);	/* XXX can't happen */
}