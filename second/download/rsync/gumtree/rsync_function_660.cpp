static void singleTableHelp(FILE * f, const struct poptOption * table, 
			    int left,
			    const char *translation_domain) {
    const struct poptOption * opt;
    const char *sub_transdom;

    opt = table;
    while (opt->longName || opt->shortName || opt->arg) {
	if ((opt->longName || opt->shortName) && 
	    !(opt->argInfo & POPT_ARGFLAG_DOC_HIDDEN))
	    singleOptionHelp(f, left, opt, translation_domain);
	opt++;
    }

    opt = table;
    while (opt->longName || opt->shortName || opt->arg) {
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    sub_transdom = getTableTranslationDomain(opt->arg);
	    if(!sub_transdom)
		sub_transdom = translation_domain;
	    
	    if (opt->descrip)
		fprintf(f, "\n%s\n", D_(sub_transdom, opt->descrip));

	    singleTableHelp(f, opt->arg, left, sub_transdom);
	}
	opt++;
    }
}