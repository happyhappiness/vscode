static int open_callback(const struct option *opt, const char *arg, int unset)
{
	struct grep_opt *grep_opt = opt->value;
	append_grep_pattern(grep_opt, "(", "command line", 0, GREP_OPEN_PAREN);
	return 0;
}