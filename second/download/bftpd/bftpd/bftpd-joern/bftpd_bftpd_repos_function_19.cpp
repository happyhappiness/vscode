void wtmp_init()
{
	if (strcasecmp(config_getoption("LOG_WTMP"), "no")) {
		if (!((wtmp = fopen(_PATH_WTMP, "a"))))
			bftpd_log("Warning: Unable to open %s.\n", _PATH_WTMP);
	}
}