int diff_tree_sha1(const unsigned char *old, const unsigned char *new, const char *base_str, struct diff_options *opt)
{
	struct strbuf base;
	int retval;

	strbuf_init(&base, PATH_MAX);
	strbuf_addstr(&base, base_str);

	retval = ll_diff_tree_sha1(old, new, &base, opt);
	if (!*base_str && DIFF_OPT_TST(opt, FOLLOW_RENAMES) && diff_might_be_rename())
		try_to_follow_renames(old, new, &base, opt);

	strbuf_release(&base);

	return retval;
}