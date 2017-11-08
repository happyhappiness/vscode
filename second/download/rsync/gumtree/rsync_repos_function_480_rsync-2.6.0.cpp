int poptReadDefaultConfig(poptContext con, /*@unused@*/ int useEnv) {
    char * fn, * home;
    int rc;

    /*@-type@*/
    if (!con->appName) return 0;
    /*@=type@*/

    rc = poptReadConfigFile(con, "/etc/popt");
    if (rc) return rc;
    if (getuid() != geteuid()) return 0;

    if ((home = getenv("HOME"))) {
	fn = alloca(strlen(home) + 20);
	strcpy(fn, home);
	strcat(fn, "/.popt");
	rc = poptReadConfigFile(con, fn);
	if (rc) return rc;
    }

    return 0;
}