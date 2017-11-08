static const char *findNextArg(poptContext con, unsigned argx, int delete)
{
    struct optionStackEntry * os = con->os;
    const char * arg;

    do {
	int i;
	arg = NULL;
	while (os->next == os->argc && os > con->optionStack) os--;
	if (os->next == os->argc && os == con->optionStack) break;
	for (i = os->next; i < os->argc; i++) {
	    if (os->argb && PBM_ISSET(i, os->argb)) continue;
	    if (*os->argv[i] == '-') continue;
	    if (--argx > 0) continue;
	    arg = os->argv[i];
	    if (delete) {
		if (os->argb == NULL) os->argb = PBM_ALLOC(os->argc);
		PBM_SET(i, os->argb);
	    }
	    break;
	}
	if (os > con->optionStack) os--;
    } while (arg == NULL);
    return arg;
}