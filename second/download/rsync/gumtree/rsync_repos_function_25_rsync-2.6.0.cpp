BOOL lp_load(char *pszFname, int globals_only)
{
	extern int am_server;
	extern int am_daemon;
	extern int am_root;
	pstring n2;
	BOOL bRetval;

	bRetval = False;

	bInGlobalSection = True;

	init_globals();

	if (pszFname)
	    pstrcpy(n2,pszFname);
	else if (am_server && am_daemon && !am_root)
	    pstrcpy(n2,RSYNCD_USERCONF);
	else
	    pstrcpy(n2,RSYNCD_SYSCONF);

	/* We get sections first, so have to start 'behind' to make up */
	iServiceIndex = -1;
	bRetval = pm_process(n2, globals_only?NULL:do_section, do_parameter);

	return (bRetval);
}