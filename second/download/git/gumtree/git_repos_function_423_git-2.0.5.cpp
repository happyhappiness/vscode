int git_config_bool(const char *name, const char *value)
{
	int discard;
	return !!git_config_bool_or_int(name, value, &discard);
}