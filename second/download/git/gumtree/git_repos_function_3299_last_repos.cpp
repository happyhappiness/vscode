static void queue_diffs(struct line_log_data *range,
			struct diff_options *opt,
			struct diff_queue_struct *queue,
			struct commit *commit, struct commit *parent)
{
	assert(commit);

	DIFF_QUEUE_CLEAR(&diff_queued_diff);
	diff_tree_oid(parent ? &parent->tree->object.oid : NULL,
		      &commit->tree->object.oid, "", opt);
	if (opt->detect_rename) {
		filter_diffs_for_paths(range, 1);
		if (diff_might_be_rename())
			diffcore_std(opt);
		filter_diffs_for_paths(range, 0);
	}
	move_diff_queue(queue, &diff_queued_diff);
}