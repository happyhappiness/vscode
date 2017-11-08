static int is_dev_null(const char *str)
{
	return !memcmp("/dev/null", str, 9) && isspace(str[9]);
}