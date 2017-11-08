void poptSetOtherOptionHelp(poptContext con, const char * text) {
    if (con->otherHelp) xfree(con->otherHelp);
    con->otherHelp = xstrdup(text);
}