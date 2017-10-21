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

static int execCommand(poptContext con)
    /*@*/
{
    poptItem item = con->doExec;
    const char ** argv;
    int argc = 0;
    int rc;

    if (item == NULL) /*XXX can't happen*/
	return POPT_ERROR_NOARG;

    if (item->argv == NULL || item->argc < 1 ||
	(!con->execAbsolute && strchr(item->argv[0], '/')))
	    return POPT_ERROR_NOARG;

    argv = malloc(sizeof(*argv) *
			(6 + item->argc + con->numLeftovers + con->finalArgvCount));
    if (argv == NULL) return POPT_ERROR_MALLOC;	/* XXX can't happen */

    if (!strchr(item->argv[0], '/') && con->execPath) {
	char *s = alloca(strlen(con->execPath) + strlen(item->argv[0]) + sizeof("/"));
	sprintf(s, "%s/%s", con->execPath, item->argv[0]);
	argv[argc] = s;
    } else {
	argv[argc] = findProgramPath(item->argv[0]);
    }
    if (argv[argc++] == NULL) return POPT_ERROR_NOARG;

    if (item->argc > 1) {
	memcpy(argv + argc, item->argv + 1, sizeof(*argv) * (item->argc - 1));
	argc += (item->argc - 1);
    }

    if (con->finalArgv != NULL && con->finalArgvCount > 0) {
	memcpy(argv + argc, con->finalArgv,
		sizeof(*argv) * con->finalArgvCount);
	argc += con->finalArgvCount;
    }

    if (con->leftovers != NULL && con->numLeftovers > 0) {
#if 0
	argv[argc++] = "--";
#endif
	memcpy(argv + argc, con->leftovers, sizeof(*argv) * con->numLeftovers);
	argc += con->numLeftovers;
    }

    argv[argc] = NULL;

#ifdef __hpux
    rc = setresuid(getuid(), getuid(),-1);
    if (rc) return POPT_ERROR_ERRNO;
#else
/*
 * XXX " ... on BSD systems setuid() should be preferred over setreuid()"
 * XXX 	sez' Timur Bakeyev <mc@bat.ru>
 * XXX	from Norbert Warmuth <nwarmuth@privat.circular.de>
 */
#if defined(HAVE_SETUID)
    rc = setuid(getuid());
    if (rc) return POPT_ERROR_ERRNO;
#elif defined (HAVE_SETREUID)
    rc = setreuid(getuid(), getuid()); /*hlauer: not portable to hpux9.01 */
    if (rc) return POPT_ERROR_ERRNO;
#else
    ; /* Can't drop privileges */
#endif
#endif

    if (argv[0] == NULL)
	return POPT_ERROR_NOARG;
#ifdef MYDEBUG
    {	const char ** avp;
	fprintf(stderr, "==> execvp(%s) argv[%d]:", argv[0], argc);
	for (avp = argv; *avp; avp++)
	    fprintf(stderr, " '%s'", *avp);
	fprintf(stderr, "\n");
    }
#endif

    rc = execvp(argv[0], (char *const *)argv);
    return POPT_ERROR_ERRNO;
}

/*@observer@*/ /*@null@*/ static const struct poptOption *
findOption(const struct poptOption * opt, /*@null@*/ const char * longName,
		char shortName,
		/*@null@*/ /*@out@*/ poptCallbackType * callback,
		/*@null@*/ /*@out@*/ const void ** callbackData,
		int singleDash)
	/*@modifies *callback, *callbackData */
{
    const struct poptOption * cb = NULL;

    /* This happens when a single - is given */
    if (singleDash && !shortName && (longName && *longName == '\0'))
	shortName = '-';

    for (; opt->longName || opt->shortName || opt->arg; opt++) {

	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    const struct poptOption * opt2;

	    /* Recurse on included sub-tables. */
	    if (opt->arg == NULL) continue;	/* XXX program error */
	    opt2 = findOption(opt->arg, longName, shortName, callback,
			      callbackData, singleDash);
	    if (opt2 == NULL) continue;
	    /* Sub-table data will be inheirited if no data yet. */
	    if (!(callback && *callback)) return opt2;
	    if (!(callbackData && *callbackData == NULL)) return opt2;
	    /*@-observertrans -dependenttrans @*/
	    *callbackData = opt->descrip;
	    /*@=observertrans =dependenttrans @*/
	    return opt2;
	} else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_CALLBACK) {
	    cb = opt;
	} else if (longName && opt->longName &&
		   (!singleDash || (opt->argInfo & POPT_ARGFLAG_ONEDASH)) &&
		/*@-nullpass@*/		/* LCL: opt->longName != NULL */
		   !strcmp(longName, opt->longName))
		/*@=nullpass@*/
	{
	    break;
	} else if (shortName && shortName == opt->shortName) {
	    break;
	}
    }

    if (!opt->longName && !opt->shortName)
	return NULL;
    /*@-modobserver -mods @*/
    if (callback) *callback = NULL;
    if (callbackData) *callbackData = NULL;
    if (cb) {
	if (callback)
	/*@-castfcnptr@*/
	    *callback = (poptCallbackType)cb->arg;
	/*@=castfcnptr@*/
	if (!(cb->argInfo & POPT_CBFLAG_INC_DATA)) {
	    if (callbackData)
		/*@-observertrans@*/	/* FIX: typedef double indirection. */
		*callbackData = cb->descrip;
		/*@=observertrans@*/
	}
    }
    /*@=modobserver =mods @*/

    return opt;
}

static const char * findNextArg(/*@special@*/ poptContext con,
		unsigned argx, int delete_arg)
	/*@uses con->optionStack, con->os,
		con->os->next, con->os->argb, con->os->argc, con->os->argv @*/
	/*@modifies con @*/
{
    struct optionStackEntry * os = con->os;
    const char * arg;

    do {
	int i;
	arg = NULL;
	while (os->next == os->argc && os > con->optionStack) os--;
	if (os->next == os->argc && os == con->optionStack) break;
	if (os->argv != NULL)
	for (i = os->next; i < os->argc; i++) {
	    /*@-sizeoftype@*/
	    if (os->argb && PBM_ISSET(i, os->argb))
		/*@innercontinue@*/ continue;
	    if (*os->argv[i] == '-')
		/*@innercontinue@*/ continue;
	    if (--argx > 0)
		/*@innercontinue@*/ continue;
	    arg = os->argv[i];
	    if (delete_arg) {
		if (os->argb == NULL) os->argb = PBM_ALLOC(os->argc);
		if (os->argb != NULL)	/* XXX can't happen */
		PBM_SET(i, os->argb);
	    }
	    /*@innerbreak@*/ break;
	    /*@=sizeoftype@*/
	}
	if (os > con->optionStack) os--;
    } while (arg == NULL);
    return arg;
}

static /*@only@*/ /*@null@*/ const char *
expandNextArg(/*@special@*/ poptContext con, const char * s)
	/*@uses con->optionStack, con->os,
		con->os->next, con->os->argb, con->os->argc, con->os->argv @*/
	/*@modifies con @*/
{
    const char * a = NULL;
    size_t alen;
    char *t, *te;
    size_t tn = strlen(s) + 1;
    char c;

    te = t = malloc(tn);;
    if (t == NULL) return NULL;		/* XXX can't happen */
    while ((c = *s++) != '\0') {
	switch (c) {
#if 0	/* XXX can't do this */
	case '\\':	/* escape */
	    c = *s++;
	    /*@switchbreak@*/ break;
#endif
	case '!':
	    if (!(s[0] == '#' && s[1] == ':' && s[2] == '+'))
		/*@switchbreak@*/ break;
	    /* XXX Make sure that findNextArg deletes only next arg. */
	    if (a == NULL) {
		if ((a = findNextArg(con, 1, 1)) == NULL)
		    /*@switchbreak@*/ break;
	    }
	    s += 3;

	    alen = strlen(a);
	    tn += alen;
	    *te = '\0';
	    t = realloc(t, tn);
	    te = t + strlen(t);
	    strncpy(te, a, alen); te += alen;
	    continue;
	    /*@notreached@*/ /*@switchbreak@*/ break;
	default:
	    /*@switchbreak@*/ break;
	}
	*te++ = c;
    }
    *te = '\0';
    t = realloc(t, strlen(t) + 1);	/* XXX memory leak, hard to plug */
    return t;
}

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

static int poptSaveLong(const struct poptOption * opt, long aLong)
	/*@modifies opt->arg @*/
{
    if (opt->arg == NULL)
	return POPT_ERROR_NULLARG;

    if (opt->argInfo & POPT_ARGFLAG_NOT)
	aLong = ~aLong;
    switch (opt->argInfo & POPT_ARGFLAG_LOGICALOPS) {
    case 0:
	*((long *) opt->arg) = aLong;
	break;
    case POPT_ARGFLAG_OR:
	*((long *) opt->arg) |= aLong;
	break;
    case POPT_ARGFLAG_AND:
	*((long *) opt->arg) &= aLong;
	break;
    case POPT_ARGFLAG_XOR:
	*((long *) opt->arg) ^= aLong;
	break;
    default:
	return POPT_ERROR_BADOPERATION;
	/*@notreached@*/ break;
    }
    return 0;
}

static int poptSaveInt(const struct poptOption * opt, long aLong)
	/*@modifies opt->arg @*/
{
    if (opt->arg == NULL)
	return POPT_ERROR_NULLARG;

    if (opt->argInfo & POPT_ARGFLAG_NOT)
	aLong = ~aLong;
    switch (opt->argInfo & POPT_ARGFLAG_LOGICALOPS) {
    case 0:
	*((int *) opt->arg) = aLong;
	break;
    case POPT_ARGFLAG_OR:
	*((int *) opt->arg) |= aLong;
	break;
    case POPT_ARGFLAG_AND:
	*((int *) opt->arg) &= aLong;
	break;
    case POPT_ARGFLAG_XOR:
	*((int *) opt->arg) ^= aLong;
	break;
    default:
	return POPT_ERROR_BADOPERATION;
	/*@notreached@*/ break;
    }
    return 0;
}

/* returns 'val' element, -1 on last item, POPT_ERROR_* on error */
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
