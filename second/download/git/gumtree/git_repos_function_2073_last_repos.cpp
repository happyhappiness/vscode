static void do_oneway_diff(struct unpack_trees_options *o,
			   const struct cache_entry *idx,
			   const struct cache_entry *tree)
{
	struct rev_info *revs = o->unpack_data;
	int match_missing, cached;

	/* i-t-a entries do not actually exist in the index */
	if (revs->diffopt.ita_invisible_in_index &&
	    idx && ce_intent_to_add(idx)) {
		idx = NULL;
		if (!tree)
			return;	/* nothing to diff.. */
	}

	/* if the entry is not checked out, don't examine work tree */
	cached = o->index_only ||
		(idx && ((idx->ce_flags & CE_VALID) || ce_skip_worktree(idx)));
	/*
	 * Backward compatibility wart - "diff-index -m" does
	 * not mean "do not ignore merges", but "match_missing".
	 *
	 * But with the revision flag parsing, that's found in
	 * "!revs->ignore_merges".
	 */
	match_missing = !revs->ignore_merges;

	if (cached && idx && ce_stage(idx)) {
		struct diff_filepair *pair;
		pair = diff_unmerge(&revs->diffopt, idx->name);
		if (tree)
			fill_filespec(pair->one, &tree->oid, 1,
				      tree->ce_mode);
		return;
	}

	/*
	 * Something added to the tree?
	 */
	if (!tree) {
		show_new_file(revs, idx, cached, match_missing);
		return;
	}

	/*
	 * Something removed from the tree?
	 */
	if (!idx) {
		diff_index_show_file(revs, "-", tree, &tree->oid, 1,
				     tree->ce_mode, 0);
		return;
	}

	/* Show difference between old and new */
	show_modified(revs, tree, idx, 1, cached, match_missing);
}