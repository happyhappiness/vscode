const char * poptGetOptArg(poptContext con)
{
    const char * ret = NULL;
    /*@-branchstate@*/
    if (con) {
	ret = con->os->nextArg;
	con->os->nextArg = NULL;
    }
    /*@=branchstate@*/
    return ret;
}