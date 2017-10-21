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

static void execCommand(poptContext con) {
    const char ** argv;
    int pos = 0;
    const char * script = con->doExec->script;

    argv = malloc(sizeof(*argv) *
			(6 + con->numLeftovers + con->finalArgvCount));

    if (!con->execAbsolute && strchr(script, '/')) return;

    if (!strchr(script, '/') && con->execPath) {
	char *s = malloc(strlen(con->execPath) + strlen(script) + 2);
	sprintf(s, "%s/%s", con->execPath, script);
	argv[pos] = s;
    } else {
	argv[pos] = script;
    }
    pos++;

    argv[pos] = findProgramPath(con->os->argv[0]);
    if (argv[pos]) pos++;
    argv[pos++] = ";";

    memcpy(argv + pos, con->finalArgv, sizeof(*argv) * con->finalArgvCount);
    pos += con->finalArgvCount;

    if (con->numLeftovers) {
	argv[pos++] = "--";
	memcpy(argv + pos, con->leftovers, sizeof(*argv) * con->numLeftovers);
	pos += con->numLeftovers;
    }

    argv[pos++] = NULL;

#ifdef __hpux
    setresuid(getuid(), getuid(),-1);
#else
/*
 * XXX " ... on BSD systems setuid() should be preferred over setreuid()"
 * XXX 	sez' Timur Bakeyev <mc@bat.ru>
 * XXX	from Norbert Warmuth <nwarmuth@privat.circular.de>
 */
#if defined(HAVE_SETUID)
    setuid(getuid());
#elif defined (HAVE_SETREUID)
    setreuid(getuid(), getuid()); /*hlauer: not portable to hpux9.01 */
#else
    ; /* Can't drop privileges */
#endif
#endif

    execvp(argv[0], (char *const *)argv);
}

/*@observer@*/ static const struct poptOption *
findOption(const struct poptOption * table, const char * longName,
    char shortName,
    /*@out@*/ poptCallbackType * callback, /*@out@*/ const void ** callbackData,
    int singleDash)
{
    const struct poptOption * opt = table;
    const struct poptOption * opt2;
    const struct poptOption * cb = NULL;

    /* This happens when a single - is given */
    if (singleDash && !shortName && !*longName)
	shortName = '-';

    while (opt->longName || opt->shortName || opt->arg) {
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    opt2 = findOption(opt->arg, longName, shortName, callback,
			      callbackData, singleDash);
	    if (opt2) {
		if (*callback && !*callbackData)
		    *callbackData = opt->descrip;
		return opt2;
	    }
	} else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_CALLBACK) {
	    cb = opt;
	} else if (longName && opt->longName &&
		   (!singleDash || (opt->argInfo & POPT_ARGFLAG_ONEDASH)) &&
		   !strcmp(longName, opt->longName)) {
	    break;
	} else if (shortName && shortName == opt->shortName) {
	    break;
	}
	opt++;
    }

    if (!opt->longName && !opt->shortName) return NULL;
    *callbackData = NULL;
    *callback = NULL;
    if (cb) {
	*callback = (poptCallbackType)cb->arg;
	if (!(cb->argInfo & POPT_CBFLAG_INC_DATA))
	    *callbackData = cb->descrip;
    }

    return opt;
}

static const char *findNextArg(poptContext con, unsigned argx, int delete)
{
    struct optionStackEntry * os = con->os;
    const char * arg;

    do {
	int i;
	arg = NULL;
	while (os->next == os->argc && os > con->optionStack) os--;
	if (os->next == os->argc && os == con->optionStack) break;
	for (i = os->next; i < os->argc; i++) {
	    if (os->argb && PBM_ISSET(i, os->argb)) continue;
	    if (*os->argv[i] == '-') continue;
	    if (--argx > 0) continue;
	    arg = os->argv[i];
	    if (delete) {
		if (os->argb == NULL) os->argb = PBM_ALLOC(os->argc);
		PBM_SET(i, os->argb);
	    }
	    break;
	}
	if (os > con->optionStack) os--;
    } while (arg == NULL);
    return arg;
}

static /*@only@*/ const char * expandNextArg(poptContext con, const char * s)
{
    const char *a;
    size_t alen;
    char *t, *te;
    size_t tn = strlen(s) + 1;
    char c;

    te = t = malloc(tn);;
    while ((c = *s++) != '\0') {
	switch (c) {
#if 0	/* XXX can't do this */
	case '\\':	/* escape */
	    c = *s++;
	    break;
#endif
	case '!':
	    if (!(s[0] == '#' && s[1] == ':' && s[2] == '+'))
		break;
	    if ((a = findNextArg(con, 1, 1)) == NULL)
		break;
	    s += 3;

	    alen = strlen(a);
	    tn += alen;
	    *te = '\0';
	    t = realloc(t, tn);
	    te = t + strlen(t);
	    strncpy(te, a, alen); te += alen;
	    continue;
	    /*@notreached@*/ break;
	default:
	    break;
	}
	*te++ = c;
    }
    *te = '\0';
    t = realloc(t, strlen(t)+1);	/* XXX memory leak, hard to plug */
    return t;
}

static void poptStripArg(poptContext con, int which)
{
    if(con->arg_strip == NULL) {
	con->arg_strip = PBM_ALLOC(con->optionStack[0].argc);
    }
    PBM_SET(which, con->arg_strip);
}

/* returns 'val' element, -1 on last item, POPT_ERROR_* on error */
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
