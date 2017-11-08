void poptPrintUsage(poptContext con, FILE * fp, /*@unused@*/ int flags)
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

    fprintf(fp, "\n");
}