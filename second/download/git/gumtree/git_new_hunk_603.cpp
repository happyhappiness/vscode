		die_no_merge_candidates(repo, refspecs);

	if (is_null_sha1(orig_head)) {
		if (merge_heads.nr > 1)
			die(_("Cannot merge multiple branches into empty head."));
		return pull_into_void(*merge_heads.sha1, curr_head);
	}
	if (opt_rebase && merge_heads.nr > 1)
		die(_("Cannot rebase onto multiple branches."));

	if (opt_rebase) {
		struct commit_list *list = NULL;
		struct commit *merge_head, *head;

		head = lookup_commit_reference(orig_head);
		commit_list_insert(head, &list);
		merge_head = lookup_commit_reference(merge_heads.sha1[0]);
		if (is_descendant_of(merge_head, list)) {
			/* we can fast-forward this without invoking rebase */
			opt_ff = "--ff-only";
			return run_merge();
		}
		return run_rebase(curr_head, *merge_heads.sha1, rebase_fork_point);
	} else {
		return run_merge();
	}
}
