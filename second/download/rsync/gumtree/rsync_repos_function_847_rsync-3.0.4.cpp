static size_t singleOptionUsage(FILE * fp, size_t cursor, 
		const struct poptOption * opt,
		/*@null@*/ const char *translation_domain)
	/*@globals fileSystem @*/
	/*@modifies *fp, fileSystem @*/
{
    size_t len = 4;
    char shortStr[2] = { '\0', '\0' };
    const char * item = shortStr;
    const char * argDescrip = getArgDescrip(opt, translation_domain);

    if (opt->shortName != '\0' && opt->longName != NULL) {
	len += 2;
	if (!(opt->argInfo & POPT_ARGFLAG_ONEDASH)) len++;
	len += strlen(opt->longName);
    } else if (opt->shortName != '\0') {
	len++;
	shortStr[0] = opt->shortName;
	shortStr[1] = '\0';
    } else if (opt->longName) {
	len += strlen(opt->longName);
	if (!(opt->argInfo & POPT_ARGFLAG_ONEDASH)) len++;
	item = opt->longName;
    }

    if (len == 4) return cursor;

#ifdef POPT_WCHAR_HACK
    /* XXX Calculate no. of display characters. */
    if (argDescrip) {
	const char * scopy = argDescrip;
	mbstate_t t;
	size_t n;

/*@-boundswrite@*/
	memset ((void *)&t, '\0', sizeof (t));	/* In initial state.  */
/*@=boundswrite@*/
	/* Determine number of characters.  */
	n = mbsrtowcs (NULL, &scopy, strlen(scopy), &t);
	len += sizeof("=")-1 + n;
    }
#else
    if (argDescrip) 
	len += sizeof("=")-1 + strlen(argDescrip);
#endif

    if ((cursor + len) > 79) {
	fprintf(fp, "\n       ");
	cursor = 7;
    } 

    if (opt->longName && opt->shortName) {
	fprintf(fp, " [-%c|-%s%s%s%s]",
	    opt->shortName, ((opt->argInfo & POPT_ARGFLAG_ONEDASH) ? "" : "-"),
	    opt->longName,
	    (argDescrip ? " " : ""),
	    (argDescrip ? argDescrip : ""));
    } else {
	fprintf(fp, " [-%s%s%s%s]",
	    ((opt->shortName || (opt->argInfo & POPT_ARGFLAG_ONEDASH)) ? "" : "-"),
	    item,
	    (argDescrip ? (opt->shortName != '\0' ? " " : "=") : ""),
	    (argDescrip ? argDescrip : ""));
    }

    return cursor + len + 1;
}