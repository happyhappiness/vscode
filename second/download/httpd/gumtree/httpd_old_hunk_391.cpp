     * Anyway, simply return a fork().
     */
    if (strcmp(os_version.release, "01.0A") == 0 ||
	strcmp(os_version.release, "02.0A") == 0 ||
	strcmp(os_version.release, "02.1A") == 0)
    {
	ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, NULL,
		     "Error: unsupported OS version. "
		     "You may encounter problems.");
	forktype = bs2_FORK;
    }

    /* The following versions are special:
