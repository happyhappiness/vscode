
	if (!argc)
		usage_with_options(builtin_merge_usage,
			builtin_merge_options);

	if (!head_commit) {
		struct commit *remote_head;
		/*
		 * If the merged head is a valid one there is no reason
		 * to forbid "git merge" into a branch yet to be born.
		 * We do the same for "git pull".
		 */
		if (squash)
			die(_("Squash commit into empty head not supported yet"));
		if (fast_forward == FF_NO)
			die(_("Non-fast-forward commit does not make sense into "
			    "an empty head"));
		remoteheads = collect_parents(head_commit, &head_subsumed,
					      argc, argv, NULL);
		remote_head = remoteheads->item;
		if (!remote_head)
			die(_("%s - not something we can merge"), argv[0]);
		if (remoteheads->next)
			die(_("Can merge only exactly one commit into empty head"));
		read_empty(remote_head->object.oid.hash, 0);
		update_ref("initial pull", "HEAD", remote_head->object.oid.hash,
			   NULL, 0, UPDATE_REFS_DIE_ON_ERR);
		goto done;
	}

	/*
	 * This could be traditional "merge <msg> HEAD <commit>..."  and
