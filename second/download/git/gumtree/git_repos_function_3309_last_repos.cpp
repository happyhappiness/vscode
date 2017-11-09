int line_log_print(struct rev_info *rev, struct commit *commit)
{
	struct line_log_data *range = lookup_line_range(rev, commit);

	show_log(rev);
	dump_diff_hacky(rev, range);
	return 1;
}