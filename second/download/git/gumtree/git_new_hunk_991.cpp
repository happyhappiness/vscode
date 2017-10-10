	struct strbuf buf = STRBUF_INIT;
	char *expanded;

	if (!path)
		return config_error_nonbool("include.path");

	expanded = expand_user_path(path, 0);
	if (!expanded)
		return error("could not expand include path '%s'", path);
	path = expanded;

	/*
	 * Use an absolute path as-is, but interpret relative paths
