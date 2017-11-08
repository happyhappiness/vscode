const char * poptGetOptArg(poptContext con) {
    const char * ret = con->os->nextArg;
    con->os->nextArg = NULL;
    return ret;
}