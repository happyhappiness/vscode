	return sys_errlist[errno];
    else
	return POPT_("unknown errno");
}
#endif

void poptSetExecPath(poptContext con, const char * path, int allowAbsolute) {
    if (con->execPath) xfree(con->execPath);
    con->execPath = xstrdup(path);
    con->execAbsolute = allowAbsolute;
}

static void invokeCallbacks(poptContext con, const struct poptOption * table,
			    int post) {
    const struct poptOption * opt = table;
    poptCallbackType cb;

    while (opt->longName || opt->shortName || opt->arg) {
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    invokeCallbacks(con, opt->arg, post);
	} else if (((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_CALLBACK) &&
		   ((!post && (opt->argInfo & POPT_CBFLAG_PRE)) ||
		    ( post && (opt->argInfo & POPT_CBFLAG_POST)))) {
	    cb = (poptCallbackType)opt->arg;
	    cb(con, post ? POPT_CALLBACK_REASON_POST : POPT_CALLBACK_REASON_PRE,
	       NULL, NULL, opt->descrip);
	}
	opt++;
    }
}

poptContext poptGetContext(const char * name, int argc, const char ** argv,
			   const struct poptOption * options, int flags) {
    poptContext con = malloc(sizeof(*con));

    memset(con, 0, sizeof(*con));

    con->os = con->optionStack;
    con->os->argc = argc;
    con->os->argv = argv;
    con->os->argb = NULL;

    if (!(flags & POPT_CONTEXT_KEEP_FIRST))
	con->os->next = 1;			/* skip argv[0] */

    con->leftovers = calloc( (argc + 1), sizeof(char *) );
    con->options = options;
    con->aliases = NULL;
    con->numAliases = 0;
    con->flags = flags;
    con->execs = NULL;
    con->numExecs = 0;
    con->finalArgvAlloced = argc * 2;
