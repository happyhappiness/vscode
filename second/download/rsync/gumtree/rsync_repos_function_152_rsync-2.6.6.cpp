void show_argvs(int argc, char *argv[])
{
	int i;

	rprintf(FINFO, "BATCH.C:show_argvs,argc=%d\n", argc);
	for (i = 0; i < argc; i++)
		rprintf(FINFO, "i=%d,argv[i]=%s\n", i, safe_fname(argv[i]));
}