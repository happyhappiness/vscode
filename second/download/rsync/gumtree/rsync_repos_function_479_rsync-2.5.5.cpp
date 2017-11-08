static void cleanOSE(struct optionStackEntry *os)
{
    if (os->nextArg) {
	xfree(os->nextArg);
	os->nextArg = NULL;
    }
    if (os->argv) {
	xfree(os->argv);
	os->argv = NULL;
    }
    if (os->argb) {
	PBM_FREE(os->argb);
	os->argb = NULL;
    }
}