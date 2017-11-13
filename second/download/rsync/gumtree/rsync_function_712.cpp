void poptPrintHelp(poptContext con, FILE * f, /*@unused@*/ int flags) {
    int leftColWidth;

    showHelpIntro(con, f);
    if (con->otherHelp)
	fprintf(f, " %s\n", con->otherHelp);
    else
	fprintf(f, " %s\n", POPT_("[OPTION...]"));

    leftColWidth = maxArgWidth(con->options, NULL);
    singleTableHelp(f, con->options, leftColWidth, NULL);
}