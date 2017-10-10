		die_no_merge_candidates(repo, refspecs);

	if (is_null_sha1(orig_head)) {
		if (merge_heads.nr > 1)
			die(_("Cannot merge multiple branches into empty head."));
		return pull_into_void(*merge_heads.sha1, curr_head);
	} else if (opt_rebase) {
		if (merge_heads.nr > 1)
			die(_("Cannot rebase onto multiple branches."));
		return run_rebase(curr_head, *merge_heads.sha1, rebase_fork_point);
	} else
		return run_merge();
}
