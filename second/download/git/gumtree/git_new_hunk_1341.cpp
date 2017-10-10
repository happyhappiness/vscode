		return pull_into_void(merge_heads.oid, &curr_head);
	}
	if (opt_rebase && merge_heads.nr > 1)
		die(_("Cannot rebase onto multiple branches."));

	if (opt_rebase) {
		int ret = 0;
		if ((recurse_submodules == RECURSE_SUBMODULES_ON ||
		     recurse_submodules == RECURSE_SUBMODULES_ON_DEMAND) &&
		    submodule_touches_in_range(&rebase_fork_point, &curr_head))
			die(_("cannot rebase with locally recorded submodule modifications"));
		if (!autostash) {
			struct commit_list *list = NULL;
			struct commit *merge_head, *head;

			head = lookup_commit_reference(&orig_head);
			commit_list_insert(head, &list);
			merge_head = lookup_commit_reference(&merge_heads.oid[0]);
			if (is_descendant_of(merge_head, list)) {
				/* we can fast-forward this without invoking rebase */
				opt_ff = "--ff-only";
				ret = run_merge();
			}
		}
		ret = run_rebase(&curr_head, merge_heads.oid, &rebase_fork_point);

		if (!ret && (recurse_submodules == RECURSE_SUBMODULES_ON ||
			     recurse_submodules == RECURSE_SUBMODULES_ON_DEMAND))
			ret = rebase_submodules();

		return ret;
	} else {
		int ret = run_merge();
		if (!ret && (recurse_submodules == RECURSE_SUBMODULES_ON ||
			     recurse_submodules == RECURSE_SUBMODULES_ON_DEMAND))
			ret = update_submodules();
		return ret;
	}
}
