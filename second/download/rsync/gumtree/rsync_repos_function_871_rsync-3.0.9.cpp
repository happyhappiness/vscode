static int showHelpIntro(poptContext con, FILE * fp)
	/*@globals fileSystem @*/
	/*@modifies *fp, fileSystem @*/
{
    int len = 6;
    const char * fn;

    fprintf(fp, POPT_("Usage:"));
    if (!(con->flags & POPT_CONTEXT_KEEP_FIRST)) {
/*@-boundsread@*/
	/*@-nullderef -type@*/	/* LCL: wazzup? */
	fn = con->optionStack->argv[0];
	/*@=nullderef =type@*/
/*@=boundsread@*/
	if (fn == NULL) return len;
	if (strchr(fn, '/')) fn = strrchr(fn, '/') + 1;
	fprintf(fp, " %s", fn);
	len += strlen(fn) + 1;
    }

    return len;
}