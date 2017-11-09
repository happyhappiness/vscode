int64_t git_config_int64(const char *name, const char *value)
{
	int64_t ret;
	if (!git_parse_int64(value, &ret))
		die_bad_number(name, value);
	return ret;
}