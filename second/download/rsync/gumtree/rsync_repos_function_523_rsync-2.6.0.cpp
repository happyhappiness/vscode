static int itemUsage(FILE * fp, int cursor, poptItem item, int nitems,
		/*@null@*/ const char * translation_domain)
	/*@globals fileSystem @*/
	/*@modifies *fp, fileSystem @*/
{
    int i;

    /*@-branchstate@*/		/* FIX: W2DO? */
    if (item != NULL)
    for (i = 0; i < nitems; i++, item++) {
	const struct poptOption * opt;
	opt = &item->option;
        if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INTL_DOMAIN) {
	    translation_domain = (const char *)opt->arg;
	} else if ((opt->longName || opt->shortName) &&
		 !(opt->argInfo & POPT_ARGFLAG_DOC_HIDDEN)) {
	    cursor = singleOptionUsage(fp, cursor, opt, translation_domain);
	}
    }
    /*@=branchstate@*/

    return cursor;
}