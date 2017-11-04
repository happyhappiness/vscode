static int singleOptionUsage(FILE * fp, int cursor, 
		const struct poptOption * opt,
		/*@null@*/ const char *translation_domain)
	/*@globals fileSystem @*/
	/*@modifies *fp, fileSystem @*/
{
    int len = 3;
    char shortStr[2] = { '\0', '\0' };
    const char * item = shortStr;
    const char * argDescrip = getArgDescrip(opt, translation_domain);

    if (opt->shortName!= '\0' ) {
	if (!(opt->argInfo & POPT_ARG_MASK)) 
	    return cursor;	/* we did these already */
	len++;
	shortStr[0] = opt->shortName;
	shortStr[1] = '\0';
    } else if (opt->longName) {
	len += 1 + strlen(opt->longName);
	item = opt->longName;
    }

    if (len == 3) return cursor;

    if (argDescrip) 
	len += strlen(argDescrip) + 1;

    if ((cursor + len) > 79) {
	fprintf(fp, "\n       ");
	cursor = 7;
    } 

    fprintf(fp, " [-%s%s%s%s]",
	((opt->shortName || (opt->argInfo & POPT_ARGFLAG_ONEDASH)) ? "" : "-"),
	item,
	(argDescrip ? (opt->shortName != '\0' ? " " : "=") : ""),
	(argDescrip ? argDescrip : ""));

    return cursor + len + 1;
}