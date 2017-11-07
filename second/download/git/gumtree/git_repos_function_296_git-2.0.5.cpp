static int index_format_config(const char *var, const char *value, void *cb)
{
	unsigned int *version = cb;
	if (!strcmp(var, "index.version")) {
		*version = git_config_int(var, value);
		return 0;
	}
	return 1;
}