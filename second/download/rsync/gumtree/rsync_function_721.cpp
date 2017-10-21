void poptPrintHelp(poptContext con, FILE * fp, /*@unused@*/ int flags)
{
    int leftColWidth;

    (void) showHelpIntro(con, fp);
    if (con->otherHelp)
	fprintf(fp, " %s\n", con->otherHelp);
    else
	fprintf(fp, " %s\n", POPT_("[OPTION...]"));

    leftColWidth = maxArgWidth(con->options, NULL);
    singleTableHelp(con, fp, con->options, leftColWidth, NULL);
}