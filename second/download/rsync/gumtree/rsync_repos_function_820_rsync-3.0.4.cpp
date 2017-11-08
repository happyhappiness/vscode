poptContext poptGetContext(const char * name, int argc, const char ** argv,
			   const struct poptOption * options, int flags)
{
    poptContext con = malloc(sizeof(*con));

    if (con == NULL) return NULL;	/* XXX can't happen */
    memset(con, 0, sizeof(*con));

    con->os = con->optionStack;
    con->os->argc = argc;
    /*@-dependenttrans -assignexpose@*/	/* FIX: W2DO? */
    con->os->argv = argv;
    /*@=dependenttrans =assignexpose@*/
    con->os->argb = NULL;

    if (!(flags & POPT_CONTEXT_KEEP_FIRST))
	con->os->next = 1;			/* skip argv[0] */

    con->leftovers = calloc( (argc + 1), sizeof(*con->leftovers) );
    /*@-dependenttrans -assignexpose@*/	/* FIX: W2DO? */
    con->options = options;
    /*@=dependenttrans =assignexpose@*/
    con->aliases = NULL;
    con->numAliases = 0;
    con->flags = flags;
    con->execs = NULL;
    con->numExecs = 0;
    con->finalArgvAlloced = argc * 2;
    con->finalArgv = calloc( con->finalArgvAlloced, sizeof(*con->finalArgv) );
    con->execAbsolute = 1;
    con->arg_strip = NULL;

    if (getenv("POSIXLY_CORRECT") || getenv("POSIX_ME_HARDER"))
	con->flags |= POPT_CONTEXT_POSIXMEHARDER;

    if (name) {
	size_t bufsize = strlen(name) + 1;
	char * t = malloc(bufsize);
	if (t) {
	    strlcpy(t, name, bufsize);
	    con->appName = t;
	}
    }

    /*@-internalglobs@*/
    invokeCallbacksPRE(con, con->options);
    /*@=internalglobs@*/

    return con;
}