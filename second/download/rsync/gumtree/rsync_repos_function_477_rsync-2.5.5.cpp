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