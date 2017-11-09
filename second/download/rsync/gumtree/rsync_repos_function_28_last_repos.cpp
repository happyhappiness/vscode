static int load_config(int globals_only)
{
	if (!config_file) {
		if (am_server && am_root <= 0)
			config_file = RSYNCD_USERCONF;
		else
			config_file = RSYNCD_SYSCONF;
	}
	return lp_load(config_file, globals_only);
}