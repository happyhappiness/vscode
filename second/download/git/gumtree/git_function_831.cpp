int git_config_get_expiry(const char *key, const char **output)
{
	int ret = git_config_get_string_const(key, output);
	if (ret)
		return ret;
	if (strcmp(*output, "now")) {
		unsigned long now = approxidate("now");
		if (approxidate(*output) >= now)
			git_die_config(key, _("Invalid %s: '%s'"), key, *output);
	}
	return ret;
}