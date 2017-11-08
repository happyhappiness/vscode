static void add_line_range(struct rev_info *revs, struct commit *commit,
			   struct line_log_data *range)
{
	struct line_log_data *old = NULL;
	struct line_log_data *new = NULL;

	old = lookup_decoration(&revs->line_log_data, &commit->object);
	if (old && range) {
		new = line_log_data_merge(old, range);
		free_line_log_data(old);
	} else if (range)
		new = line_log_data_copy(range);

	if (new)
		add_decoration(&revs->line_log_data, &commit->object, new);
}