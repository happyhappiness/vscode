static int singleTableUsage(FILE * f, int cursor, const struct poptOption * table,
		     const char *translation_domain) {
    const struct poptOption * opt;
    
    opt = table;
    while (opt->longName || opt->shortName || opt->arg) {
        if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INTL_DOMAIN)
	    translation_domain = (const char *)opt->arg;
	else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) 
	    cursor = singleTableUsage(f, cursor, opt->arg,
				      translation_domain);
	else if ((opt->longName || opt->shortName) && 
		 !(opt->argInfo & POPT_ARGFLAG_DOC_HIDDEN))
	  cursor = singleOptionUsage(f, cursor, opt, translation_domain);

	opt++;
    }

    return cursor;
}