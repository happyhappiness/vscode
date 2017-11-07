unsigned long git_config_ulong(const char *name, const char *value)
{
	unsigned long ret;
	if (!git_parse_ulong(value, &ret))
		die_bad_number(name, value);
	return ret;
}