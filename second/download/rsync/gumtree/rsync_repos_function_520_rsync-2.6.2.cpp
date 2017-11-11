static void itemHelp(FILE * fp,
		/*@null@*/ poptItem items, int nitems, int left,
		/*@null@*/ const char * translation_domain)
	/*@globals fileSystem @*/
	/*@modifies *fp, fileSystem @*/
{
    poptItem item;
    int i;

    if (items != NULL)
    for (i = 0, item = items; i < nitems; i++, item++) {
	const struct poptOption * opt;
	opt = &item->option;
	if ((opt->longName || opt->shortName) && 
	    !(opt->argInfo & POPT_ARGFLAG_DOC_HIDDEN))
	    singleOptionHelp(fp, left, opt, translation_domain);
    }
}