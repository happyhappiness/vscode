void NORETURN usage_msg_opt(const char *msg,
		   const char * const *usagestr,
		   const struct option *options)
{
	fprintf(stderr, "fatal: %s\n\n", msg);
	usage_with_options(usagestr, options);
}