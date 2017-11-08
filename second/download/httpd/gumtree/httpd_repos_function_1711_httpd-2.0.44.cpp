static bs2_ForkType os_forktype(void)
{
    struct utsname os_version;

    /* have we checked the OS version before? If yes return the previous
     * result - the OS release isn't going to change suddenly!
     */
    if (forktype != bs2_unknown) {
	return forktype;
    }

    /* If the user is unprivileged, use the normal fork() only. */
    if (getuid() != 0) {
	return forktype = bs2_FORK;
    }

    if (uname(&os_version) < 0)
    {
	ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
		     "uname() failed - aborting.");
	exit(APEXIT_CHILDFATAL);
    }

    /*
     * Old BS2000/OSD versions (before XPG4 SPEC1170) don't work with Apache.
     * Anyway, simply return a fork().
     */
    if (strcmp(os_version.release, "01.0A") == 0 ||
	strcmp(os_version.release, "02.0A") == 0 ||
	strcmp(os_version.release, "02.1A") == 0)
    {
	ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
		     "Error: unsupported OS version. "
		     "You may encounter problems.");
	forktype = bs2_FORK;
    }

    /* The following versions are special:
     * OS versions before A17 needs regular fork() and _rini().
     * A17 requires _rfork() and _rini(),
     * and later versions need ufork().
     */
    else if (strcmp(os_version.release, "01.1A") == 0 ||
	     strcmp(os_version.release, "03.0A") == 0 ||
	     strcmp(os_version.release, "03.1A") == 0 ||
	     strcmp(os_version.release, "04.0A") == 0)
    {
        if (strcmp (os_version.version, "A18") >= 0)
            forktype = bs2_UFORK;

	else if (strcmp (os_version.version, "A17") < 0)
            forktype = bs2_FORK_RINI;

	else
	    forktype = bs2_RFORK_RINI;
    }

    /* All later OS versions will hopefully use ufork() only  ;-) */
    else
        forktype = bs2_UFORK;

    return forktype;
}