static int log_tree_diff(struct rev_info *opt, struct commit *commit, struct log_info *log)
{
	int showed_log;
	struct commit_list *parents;
	struct object_id *oid;

	if (!opt->diff && !DIFF_OPT_TST(&opt->diffopt, EXIT_WITH_STATUS))
		return 0;

	parse_commit_or_die(commit);
	oid = &commit->tree->object.oid;

	/* Root commit? */
	parents = get_saved_parents(opt, commit);
	if (!parents) {
		if (opt->show_root_diff) {
			diff_root_tree_oid(oid, "", &opt->diffopt);
			log_tree_diff_flush(opt);
		}
		return !opt->loginfo;
	}

	/* More than one parent? */
	if (parents && parents->next) {
		if (opt->ignore_merges)
			return 0;
		else if (opt->combine_merges)
			return do_diff_combined(opt, commit);
		else if (opt->first_parent_only) {
			/*
			 * Generate merge log entry only for the first
			 * parent, showing summary diff of the others
			 * we merged _in_.
			 */
			parse_commit_or_die(parents->item);
			diff_tree_oid(&parents->item->tree->object.oid,
				      oid, "", &opt->diffopt);
			log_tree_diff_flush(opt);
			return !opt->loginfo;
		}

		/* If we show individual diffs, show the parent info */
		log->parent = parents->item;
	}

	showed_log = 0;
	for (;;) {
		struct commit *parent = parents->item;

		parse_commit_or_die(parent);
		diff_tree_oid(&parent->tree->object.oid,
			      oid, "", &opt->diffopt);
		log_tree_diff_flush(opt);

		showed_log |= !opt->loginfo;

		/* Set up the log info for the next parent, if any.. */
		parents = parents->next;
		if (!parents)
			break;
		log->parent = parents->item;
		opt->loginfo = log;
	}
	return showed_log;
}