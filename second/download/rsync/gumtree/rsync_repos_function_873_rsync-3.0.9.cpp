static int showShortOptions(const struct poptOption * opt, FILE * fp,
		/*@null@*/ char * str)
	/*@globals fileSystem @*/
	/*@modifies *str, *fp, fileSystem @*/
	/*@requires maxRead(str) >= 0 @*/
{
    /* bufsize larger then the ascii set, lazy alloca on top level call. */
    char * s = (str != NULL ? str : memset(alloca(300), 0, 300));
    int len = 0;

    if (s == NULL)
	return 0;

/*@-boundswrite@*/
    if (opt != NULL)
    for (; (opt->longName || opt->shortName || opt->arg); opt++) {
	if (opt->shortName && !(opt->argInfo & POPT_ARG_MASK))
	    s[strlen(s)] = opt->shortName;
	else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE)
	    if (opt->arg)	/* XXX program error */
		len = showShortOptions(opt->arg, fp, s);
    } 
/*@=boundswrite@*/

    /* On return to top level, print the short options, return print length. */
    if (s == str && *s != '\0') {
	fprintf(fp, " [-%s]", s);
	len = strlen(s) + sizeof(" [-]")-1;
    }
    return len;
}