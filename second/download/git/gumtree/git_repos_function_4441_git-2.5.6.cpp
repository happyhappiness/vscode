static int is_dev_null(const char *str)
{
	return skip_prefix(str, "/dev/null", &str) && isspace(*str);
}