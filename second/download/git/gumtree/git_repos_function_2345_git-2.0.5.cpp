static int http_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "http.getanyfile")) {
		getanyfile = git_config_bool(var, value);
		return 0;
	}

	if (starts_with(var, "http.")) {
		int i;

		for (i = 0; i < ARRAY_SIZE(rpc_service); i++) {
			struct rpc_service *svc = &rpc_service[i];
			if (!strcmp(var + 5, svc->config_name)) {
				svc->enabled = git_config_bool(var, value);
				return 0;
			}
		}
	}

	/* we are not interested in parsing any other configuration here */
	return 0;
}