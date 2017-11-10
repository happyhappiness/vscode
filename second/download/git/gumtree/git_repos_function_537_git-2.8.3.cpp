int git_config_maybe_bool(const char *name, const char *value)
{
	int v = git_parse_maybe_bool(value);
	if (0 <= v)
		return v;
	if (git_parse_int(value, &v))
		return !!v;
	return -1;
}