static int opt_parse_merge_filter(const struct option *opt, const char *arg, int unset)
{
	merge_filter = ((opt->long_name[0] == 'n')
			? SHOW_NOT_MERGED
			: SHOW_MERGED);
	if (unset)
		merge_filter = SHOW_NOT_MERGED; /* b/c for --no-merged */
	if (!arg)
		arg = "HEAD";
	if (get_sha1(arg, merge_filter_ref))
		die(_("malformed object name %s"), arg);
	return 0;
}