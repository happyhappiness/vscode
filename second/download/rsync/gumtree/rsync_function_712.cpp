static int showHelpIntro(poptContext con, FILE * f) {
    int len = 6;
    const char * fn;

    fprintf(f, POPT_("Usage:"));
    if (!(con->flags & POPT_CONTEXT_KEEP_FIRST)) {
	fn = con->optionStack->argv[0];
	if (strchr(fn, '/')) fn = strchr(fn, '/') + 1;
	fprintf(f, " %s", fn);
	len += strlen(fn) + 1;
    }

    return len;
}