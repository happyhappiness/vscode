static int singleTableUsage(poptContext con, FILE * fp,
		int cursor, const struct poptOption * opt,
		/*@null@*/ const char * translation_domain)
	/*@globals fileSystem @*/
	/*@modifies *fp, fileSystem @*/
{
    /*@-branchstate@*/		/* FIX: W2DO? */
    if (opt != NULL)
    for (; (opt->longName || opt->shortName || opt->arg) ; opt++) {
        if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INTL_DOMAIN) {
	    translation_domain = (const char *)opt->arg;
	} else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    if (opt->arg)	/* XXX program error */
	    cursor = singleTableUsage(con, fp, cursor, opt->arg,
			translation_domain);
	} else if ((opt->longName || opt->shortName) &&
		 !(opt->argInfo & POPT_ARGFLAG_DOC_HIDDEN)) {
	    cursor = singleOptionUsage(fp, cursor, opt, translation_domain);
	}
    }
    /*@=branchstate@*/

    return cursor;
}