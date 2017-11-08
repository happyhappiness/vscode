BOOL lp_load(char *pszFname, int globals_only)
{
	pstring n2;
	BOOL bRetval;

	bRetval = False;

	bInGlobalSection = True;

	init_globals();

	pstrcpy(n2, pszFname);

	/* We get sections first, so have to start 'behind' to make up */
	iServiceIndex = -1;
	bRetval = pm_process(n2, globals_only?NULL:do_section, do_parameter);

	return (bRetval);
}