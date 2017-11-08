static void clear_commit_line_range(struct rev_info *revs, struct commit *commit)
{
	struct line_log_data *r;
	r = lookup_decoration(&revs->line_log_data, &commit->object);
	if (!r)
		return;
	free_line_log_data(r);
	add_decoration(&revs->line_log_data, &commit->object, NULL);
}