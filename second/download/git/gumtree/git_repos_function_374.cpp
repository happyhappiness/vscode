static int credential_config_callback(const char *var, const char *value,
				      void *data)
{
	struct credential *c = data;
	const char *key, *dot;

	if (!skip_prefix(var, "credential.", &key))
		return 0;

	if (!value)
		return config_error_nonbool(var);

	dot = strrchr(key, '.');
	if (dot) {
		struct credential want = CREDENTIAL_INIT;
		char *url = xmemdupz(key, dot - key);
		int matched;

		credential_from_url(&want, url);
		matched = credential_match(&want, c);

		credential_clear(&want);
		free(url);

		if (!matched)
			return 0;
		key = dot + 1;
	}

	if (!strcmp(key, "helper"))
		string_list_append(&c->helpers, value);
	else if (!strcmp(key, "username")) {
		if (!c->username)
			c->username = xstrdup(value);
	}
	else if (!strcmp(key, "usehttppath"))
		c->use_http_path = git_config_bool(var, value);

	return 0;
}