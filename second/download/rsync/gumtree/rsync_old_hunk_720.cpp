	len += strlen(fn) + 1;
    }

    return len;
}

void poptPrintHelp(poptContext con, FILE * fp, /*@unused@*/ int flags)
{
    int leftColWidth;

    (void) showHelpIntro(con, fp);
    if (con->otherHelp)
	fprintf(fp, " %s\n", con->otherHelp);
