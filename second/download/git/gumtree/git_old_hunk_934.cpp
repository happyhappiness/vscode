				break;
			else
				continue;
		}

		/* Automerge succeeded. */
		write_tree_trivial(result_tree);
		automerge_was_ok = 1;
		break;
	}

	/*
	 * If we have a resulting tree, that means the strategy module
	 * auto resolved the merge cleanly.
	 */
	if (automerge_was_ok) {
		ret = finish_automerge(head_commit, head_subsumed,
				       common, remoteheads,
				       result_tree, wt_strategy);
		goto done;
	}

	/*
	 * Pick the result from the best strategy and have the user fix
	 * it up.
	 */
	if (!best_strategy) {
		restore_state(head_commit->object.oid.hash, stash);
		if (use_strategies_nr > 1)
			fprintf(stderr,
				_("No merge strategy handled the merge.\n"));
		else
			fprintf(stderr, _("Merge with strategy %s failed.\n"),
				use_strategies[0]->name);
		ret = 2;
		goto done;
	} else if (best_strategy == wt_strategy)
		; /* We already have its result in the working tree. */
	else {
		printf(_("Rewinding the tree to pristine...\n"));
		restore_state(head_commit->object.oid.hash, stash);
		printf(_("Using the %s to prepare resolving by hand.\n"),
			best_strategy);
		try_merge_strategy(best_strategy, common, remoteheads,
				   head_commit, head_arg);
	}

	if (squash)
		finish(head_commit, remoteheads, NULL, NULL);
	else
		write_merge_state(remoteheads);
