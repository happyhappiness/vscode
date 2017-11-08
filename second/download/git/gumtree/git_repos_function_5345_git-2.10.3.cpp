static NORETURN void error_with_usage(const char *msg)
{
	error("%s", msg);
	usage_with_options(check_attr_usage, check_attr_options);
}