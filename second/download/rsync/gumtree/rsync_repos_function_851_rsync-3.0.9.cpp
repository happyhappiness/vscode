static const struct poptOption *
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
	    void * arg = opt->arg;

/*@-branchstate@*/
	    /* XXX sick hack to preserve pretense of ABI. */
	    if (arg == poptHelpOptions) arg = poptHelpOptionsI18N;
/*@=branchstate@*/
	    /* Recurse on included sub-tables. */
	    if (arg == NULL) continue;	/* XXX program error */
	    opt2 = findOption(arg, longName, shortName, callback,
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