static int http_config(const char *var, const char *value, void *cb)
{
	const char *p;

	if (!strcmp(var, "http.getanyfile")) {
		getanyfile = git_config_bool(var, value);
		return 0;
	}

	if (skip_prefix(var, "http.", &p)) {
		int i;

		for (i = 0; i < ARRAY_SIZE(rpc_service); i++) {
			struct rpc_service *svc = &rpc_service[i];
			if (!strcmp(p, svc->config_name)) {
				svc->enabled = git_config_bool(var, value);
				return 0;
			}
		}
	}

	/* we are not interested in parsing any other configuration here */
	return 0;
}