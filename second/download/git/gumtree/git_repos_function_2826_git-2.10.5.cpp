static void dump_diff_hacky(struct rev_info *rev, struct line_log_data *range)
{
	fprintf(rev->diffopt.file, "%s\n", output_prefix(&rev->diffopt));
	while (range) {
		dump_diff_hacky_one(rev, range);
		range = range->next;
	}
}