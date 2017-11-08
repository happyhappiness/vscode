static int git_daemon_config(const char *var, const char *value, void *cb)
{
	const char *service;

	if (skip_prefix(var, "daemon.", &service) &&
	    !strcmp(service, service_looking_at->config_name)) {
		service_enabled = git_config_bool(var, value);
		return 0;
	}

	/* we are not interested in parsing any other configuration here */
	return 0;
}