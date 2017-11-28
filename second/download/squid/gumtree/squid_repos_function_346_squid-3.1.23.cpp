int
OpenConfigFile(void)
{
    FILE *ConfigFile;
    char Confbuf[2049];		/* Line reading buffer */

    /* Initialise defaults */

    Serversqueried = 0;
    memset(ServerArray, '\0', sizeof(ServerArray));
    memset(Denyuserpath, '\0', MAXPATHLEN);
    memset(Allowuserpath, '\0', MAXPATHLEN);

    /* Open file */
    if ((ConfigFile = fopen(CONFIGFILE, "r")) == NULL) {
        syslog(LOG_ERR, "OpenConfigFile: Failed to open %s.", CONFIGFILE);
        syslog(LOG_ERR, "%s", strerror(errno));
        return 1;
    }
    /* Read in, one line at a time */
    while (!feof(ConfigFile)) {
        Confbuf[0] = '\0';
        if (NULL == fgets(Confbuf, 2048, ConfigFile))
            break;
        Confbuf[2048] = '\0';
        ProcessLine(Confbuf);
    }

    /*
     * Check that at least one server is being queried. Report error if not.
     * Denied and allowed user files are hardcoded, so it's fine if they're
     * not set in the confugration file.
     */
    if (Serversqueried == 0) {
        syslog(LOG_ERR, "OpenConfigFile: No servers set in %s. At least one is needed.", CONFIGFILE);
        return 1;
    }
    fclose(ConfigFile);
    return 0;
}