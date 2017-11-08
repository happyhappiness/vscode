static void cleanOSE(/*@special@*/ struct optionStackEntry *os)
	/*@uses os @*/
	/*@releases os->nextArg, os->argv, os->argb @*/
	/*@modifies os @*/
{
    os->nextArg = _free(os->nextArg);
    os->argv = _free(os->argv);
    os->argb = PBM_FREE(os->argb);
}