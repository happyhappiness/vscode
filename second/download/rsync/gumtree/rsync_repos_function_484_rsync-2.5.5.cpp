static const struct poptOption *
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