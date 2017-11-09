ssize_t git_config_ssize_t(const char *name, const char *value)
{
	ssize_t ret;
	if (!git_parse_ssize_t(value, &ret))
		die_bad_number(name, value);
	return ret;
}