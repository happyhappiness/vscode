void poptPrintUsage(poptContext con, FILE * f, /*@unused@*/ int flags) {
    int cursor;

    cursor = showHelpIntro(con, f);
    cursor += showShortOptions(con->options, f, NULL);
    singleTableUsage(f, cursor, con->options, NULL);

    if (con->otherHelp) {
	cursor += strlen(con->otherHelp) + 1;
	if (cursor > 79) fprintf(f, "\n       ");
	fprintf(f, " %s", con->otherHelp);
    }

    fprintf(f, "\n");
}