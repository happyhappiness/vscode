int diff_tree_oid(const struct object_id *old_oid,
		  const struct object_id *new_oid,
		  const char *base_str, struct diff_options *opt)
{
	struct strbuf base;
	int retval;

	strbuf_init(&base, PATH_MAX);
	strbuf_addstr(&base, base_str);

	retval = ll_diff_tree_oid(old_oid, new_oid, &base, opt);
	if (!*base_str && DIFF_OPT_TST(opt, FOLLOW_RENAMES) && diff_might_be_rename())
		try_to_follow_renames(old_oid, new_oid, &base, opt);

	strbuf_release(&base);

	return retval;
}