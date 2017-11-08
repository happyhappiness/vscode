static int maxArgWidth(const struct poptOption * opt,
		       const char * translation_domain) {
    int max = 0;
    int this;
    const char * s;
    
    while (opt->longName || opt->shortName || opt->arg) {
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    this = maxArgWidth(opt->arg, translation_domain);
	    if (this > max) max = this;
	} else if (!(opt->argInfo & POPT_ARGFLAG_DOC_HIDDEN)) {
	    this = opt->shortName ? 2 : 0;
	    if (opt->longName) {
		if (this) this += 2;
		this += strlen(opt->longName) + 2;
	    }

	    s = getArgDescrip(opt, translation_domain);
	    if (s)
		this += strlen(s) + 1;
	    if (this > max) max = this;
	}

	opt++;
    }
    
    return max;
}