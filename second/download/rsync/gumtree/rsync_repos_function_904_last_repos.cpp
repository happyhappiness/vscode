static void invokeCallbacksPOST(poptContext con, const struct poptOption * opt)
	/*@globals internalState@*/
	/*@modifies internalState@*/
{
    if (opt != NULL)
    for (; opt->longName || opt->shortName || opt->arg; opt++) {
	if (opt->arg == NULL) continue;		/* XXX program error. */
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    void * arg = opt->arg;
/*@-branchstate@*/
	    /* XXX sick hack to preserve pretense of ABI. */
	    if (arg == poptHelpOptions) arg = poptHelpOptionsI18N;
/*@=branchstate@*/
	    /* Recurse on included sub-tables. */
	    invokeCallbacksPOST(con, arg);
	} else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_CALLBACK &&
		   (opt->argInfo & POPT_CBFLAG_POST))
	{   /*@-castfcnptr@*/
	    poptCallbackType cb = (poptCallbackType)opt->arg;
	    /*@=castfcnptr@*/
	    /* Perform callback. */
	    /*@-noeffectuncon @*/
	    cb(con, POPT_CALLBACK_REASON_POST, NULL, NULL, opt->descrip);
	    /*@=noeffectuncon @*/
	}
    }
}