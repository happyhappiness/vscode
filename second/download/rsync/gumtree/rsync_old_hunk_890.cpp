    /*@=branchstate@*/

    return cursor;
}

/**
 * @param fp		output file handle
 * @param opt		option(s)
 * @param translation_domain	translation domain
 */
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

/**
 * Return concatenated short options for display.
 * @param opt		option(s)
 * @param fp		output file handle
 * @retval str		concatenation of short options
 * @return		length of display string
 */
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

void poptPrintUsage(poptContext con, FILE * fp, /*@unused@*/ UNUSED(int flags))
{
    int cursor;

    cursor = showHelpIntro(con, fp);
    cursor += showShortOptions(con->options, fp, NULL);
    (void) singleTableUsage(con, fp, cursor, con->options, NULL);
    (void) itemUsage(fp, cursor, con->aliases, con->numAliases, NULL);
    (void) itemUsage(fp, cursor, con->execs, con->numExecs, NULL);

    if (con->otherHelp) {
	cursor += strlen(con->otherHelp) + 1;
	if (cursor > 79) fprintf(fp, "\n       ");
	fprintf(fp, " %s", con->otherHelp);
    }
