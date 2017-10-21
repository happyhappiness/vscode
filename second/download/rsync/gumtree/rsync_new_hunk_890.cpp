    /*@=branchstate@*/

    return cursor;
}

/**
 * Keep track of option tables already processed.
 */
typedef struct poptDone_s {
    int nopts;
    int maxopts;
    const void ** opts;
} * poptDone;

/**
 * Display usage text for a table of options.
 * @param con		context
 * @param fp		output file handle
 * @param cursor	current display position
 * @param opt		option(s)
 * @param translation_domain	translation domain
 * @param done		tables already processed
 * @return
 */
static size_t singleTableUsage(poptContext con, FILE * fp, size_t cursor,
		/*@null@*/ const struct poptOption * opt,
		/*@null@*/ UNUSED(const char * translation_domain),
		/*@null@*/ poptDone done)
	/*@globals fileSystem @*/
	/*@modifies *fp, done, fileSystem @*/
{
    /*@-branchstate@*/		/* FIX: W2DO? */
    if (opt != NULL)
    for (; (opt->longName || opt->shortName || opt->arg) ; opt++) {
        if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INTL_DOMAIN) {
	    translation_domain = (const char *)opt->arg;
	} else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    if (done) {
		int i = 0;
		for (i = 0; i < done->nopts; i++) {
/*@-boundsread@*/
		    const void * that = done->opts[i];
/*@=boundsread@*/
		    if (that == NULL || that != opt->arg)
			/*@innercontinue@*/ continue;
		    /*@innerbreak@*/ break;
		}
		/* Skip if this table has already been processed. */
		if (opt->arg == NULL || i < done->nopts)
		    continue;
/*@-boundswrite@*/
		if (done->nopts < done->maxopts)
		    done->opts[done->nopts++] = (const void *) opt->arg;
/*@=boundswrite@*/
	    }
	    cursor = singleTableUsage(con, fp, cursor, opt->arg,
			translation_domain, done);
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
 * @todo Sub-tables should be recursed.
 * @param opt		option(s)
 * @param fp		output file handle
 * @retval str		concatenation of short options
 * @return		length of display string
 */
static int showShortOptions(const struct poptOption * opt, FILE * fp,
		/*@null@*/ char * str)
	/*@globals fileSystem @*/
	/*@modifies *str, *fp, fileSystem @*/
	/*@requires maxRead(str) >= 0 @*/
{
    /* bufsize larger then the ascii set, lazy alloca on top level call. */
    char * s = (str != NULL ? str : memset(alloca(300), 0, 300));
    int len = 0;

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

void poptPrintUsage(poptContext con, FILE * fp, /*@unused@*/ UNUSED(int flags))
{
    poptDone done = memset(alloca(sizeof(*done)), 0, sizeof(*done));
    size_t cursor;

    done->nopts = 0;
    done->maxopts = 64;
    cursor = done->maxopts * sizeof(*done->opts);
/*@-boundswrite@*/
    done->opts = memset(alloca(cursor), 0, cursor);
    /*@-keeptrans@*/
    done->opts[done->nopts++] = (const void *) con->options;
    /*@=keeptrans@*/
/*@=boundswrite@*/

    cursor = showHelpIntro(con, fp);
    cursor += showShortOptions(con->options, fp, NULL);
    cursor = singleTableUsage(con, fp, cursor, con->options, NULL, done);
    cursor = itemUsage(fp, cursor, con->aliases, con->numAliases, NULL);
    cursor = itemUsage(fp, cursor, con->execs, con->numExecs, NULL);

    if (con->otherHelp) {
	cursor += strlen(con->otherHelp) + 1;
	if (cursor > 79) fprintf(fp, "\n       ");
	fprintf(fp, " %s", con->otherHelp);
    }
