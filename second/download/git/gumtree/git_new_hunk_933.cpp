	 * to ensure this.
	 */
	if (use_strategies_nr == 1 ||
	    /*
	     * Stash away the local changes so that we can try more than one.
	     */
	    save_state(&stash))
		oidclr(&stash);

	for (i = 0; i < use_strategies_nr; i++) {
		int ret;
		if (i) {
			printf(_("Rewinding the tree to pristine...\n"));
			restore_state(&head_commit->object.oid, &stash);
		}
		if (use_strategies_nr != 1)
			printf(_("Trying merge strategy %s...\n"),
				use_strategies[i]->name);
		/*
		 * Remember which strategy left the state in the working
		 * tree.
		 */
		wt_strategy = use_strategies[i]->name;

		ret = try_merge_strategy(use_strategies[i]->name,
					 common, remoteheads,
					 head_commit);
		if (!option_commit && !ret) {
			merge_was_ok = 1;
			/*
			 * This is necessary here just to avoid writing
			 * the tree, but later we will *not* exit with
			 * status code 1 because merge_was_ok is set.
