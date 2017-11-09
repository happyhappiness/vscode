static const char *
getTableTranslationDomain(/*@null@*/ const struct poptOption *table)
	/*@*/
{
    const struct poptOption *opt;

    if (table != NULL)
    for (opt = table; opt->longName || opt->shortName || opt->arg; opt++) {
	if (opt->argInfo == POPT_ARG_INTL_DOMAIN)
	    return opt->arg;
    }
    return NULL;
}