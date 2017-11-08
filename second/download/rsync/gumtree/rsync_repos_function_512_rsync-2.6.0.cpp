static void displayArgs(poptContext con,
		/*@unused@*/ enum poptCallbackReason foo,
		struct poptOption * key, 
		/*@unused@*/ const char * arg, /*@unused@*/ void * data)
	/*@globals fileSystem@*/
	/*@modifies fileSystem@*/
{
    if (key->shortName == '?')
	poptPrintHelp(con, stdout, 0);
    else
	poptPrintUsage(con, stdout, 0);
    exit(0);
}