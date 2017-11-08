static int process_ranges_ordinary_commit(struct rev_info *rev, struct commit *commit,
					  struct line_log_data *range)
{
	struct commit *parent = NULL;
	struct diff_queue_struct queue;
	struct line_log_data *parent_range;
	int changed;

	if (commit->parents)
		parent = commit->parents->item;

	queue_diffs(range, &rev->diffopt, &queue, commit, parent);
	changed = process_all_files(&parent_range, rev, &queue, range);
	if (parent)
		add_line_range(rev, parent, parent_range);
	return changed;
}