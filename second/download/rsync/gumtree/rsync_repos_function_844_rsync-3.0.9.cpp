static void invokeCallbacksOPTION(poptContext con,
				  const struct poptOption * opt,
				  const struct poptOption * myOpt,
				  /*@null@*/ const void * myData, int shorty)
	/*@globals internalState@*/
	/*@modifies internalState@*/
{
    const struct poptOption * cbopt = NULL;

    if (opt != NULL)
    for (; opt->longName || opt->shortName || opt->arg; opt++) {
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    void * arg = opt->arg;
/*@-branchstate@*/
	    /* XXX sick hack to preserve pretense of ABI. */
	    if (arg == poptHelpOptions) arg = poptHelpOptionsI18N;
/*@=branchstate@*/
	    /* Recurse on included sub-tables. */
	    if (opt->arg != NULL)	/* XXX program error */
		invokeCallbacksOPTION(con, opt->arg, myOpt, myData, shorty);
	} else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_CALLBACK &&
		  !(opt->argInfo & POPT_CBFLAG_SKIPOPTION)) {
	    /* Save callback info. */
	    cbopt = opt;
	} else if (cbopt != NULL &&
		   ((myOpt->shortName && opt->shortName && shorty &&
			myOpt->shortName == opt->shortName) ||
		    (myOpt->longName && opt->longName &&
		/*@-nullpass@*/		/* LCL: opt->longName != NULL */
			!strcmp(myOpt->longName, opt->longName)))
		/*@=nullpass@*/
		   )
	{   /*@-castfcnptr@*/
	    poptCallbackType cb = (poptCallbackType)cbopt->arg;
	    /*@=castfcnptr@*/
	    const void * cbData = (cbopt->descrip ? cbopt->descrip : myData);
	    /* Perform callback. */
	    if (cb != NULL) {	/* XXX program error */
		/*@-noeffectuncon @*/
		cb(con, POPT_CALLBACK_REASON_OPTION, myOpt,
			con->os->nextArg, cbData);
		/*@=noeffectuncon @*/
	    }
	    /* Terminate (unless explcitly continuing). */
	    if (!(cbopt->argInfo & POPT_CBFLAG_CONTINUE))
		return;
	}
    }
}