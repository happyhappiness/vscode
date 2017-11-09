static int process_ranges_arbitrary_commit(struct rev_info *rev, struct commit *commit)
{
	struct line_log_data *range = lookup_line_range(rev, commit);
	int changed = 0;

	if (range) {
		if (!commit->parents || !commit->parents->next)
			changed = process_ranges_ordinary_commit(rev, commit, range);
		else
			changed = process_ranges_merge_commit(rev, commit, range);
	}

	if (!changed)
		commit->object.flags |= TREESAME;

	return changed;
}