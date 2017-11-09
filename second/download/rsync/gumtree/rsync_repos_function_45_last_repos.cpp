int lp_load(char *pszFname, int globals_only)
{
	bInGlobalSection = True;

	reset_all_vars();

	/* We get sections first, so have to start 'behind' to make up. */
	iSectionIndex = -1;
	return pm_process(pszFname, globals_only ? NULL : do_section, do_parameter);
}