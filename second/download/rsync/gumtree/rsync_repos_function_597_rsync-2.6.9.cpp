static int showShortOptions(const struct poptOption * opt, FILE * fp,
		/*@null@*/ char * str)
	/*@globals fileSystem @*/
	/*@modifies *str, *fp, fileSystem @*/
{
    char * s = alloca(300);	/* larger then the ascii set */

    s[0] = '\0';
    /*@-branchstate@*/		/* FIX: W2DO? */
    if (str == NULL) {
	memset(s, 0, sizeof(s));
	str = s;
    }
    /*@=branchstate@*/

    if (opt != NULL)
    for (; (opt->longName || opt->shortName || opt->arg); opt++) {
	if (opt->shortName && !(opt->argInfo & POPT_ARG_MASK))
	    str[strlen(str)] = opt->shortName;
	else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE)
	    if (opt->arg)	/* XXX program error */
		(void) showShortOptions(opt->arg, fp, str);
    } 

    if (s != str || *s != '\0')
	return 0;

    fprintf(fp, " [-%s]", s);
    return strlen(s) + 4;
}