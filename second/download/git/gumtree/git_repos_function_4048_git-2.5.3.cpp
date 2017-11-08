static int add_man_viewer_info(const char *var, const char *value)
{
	const char *name, *subkey;
	int namelen;

	if (parse_config_key(var, "man", &name, &namelen, &subkey) < 0 || !name)
		return 0;

	if (!strcmp(subkey, "path")) {
		if (!value)
			return config_error_nonbool(var);
		return add_man_viewer_path(name, namelen, value);
	}
	if (!strcmp(subkey, "cmd")) {
		if (!value)
			return config_error_nonbool(var);
		return add_man_viewer_cmd(name, namelen, value);
	}

	return 0;
}