int git_config_int(const char *name, const char *value)
{
	int ret;
	if (!git_parse_int(value, &ret))
		die_bad_number(name, value);
	return ret;
}