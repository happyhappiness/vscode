int cmd_merge(int argc, const char **argv, const char *prefix)
{
	unsigned char result_tree[20];
	unsigned char stash[20];
	unsigned char head_sha1[20];
	struct commit *head_commit;
	struct strbuf buf = STRBUF_INIT;
	const char *head_arg;
	int flag, i, ret = 0, head_subsumed;
	int best_cnt = -1, merge_was_ok = 0, automerge_was_ok = 0;
	struct commit_list *common = NULL;
	const char *best_strategy = NULL, *wt_strategy = NULL;
	struct commit_list *remoteheads, *p;
	void *branch_to_free;

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(builtin_merge_usage, builtin_merge_options);

	/*
	 * Check if we are _not_ on a detached HEAD, i.e. if there is a
	 * current branch.
	 */
	branch = branch_to_free = resolve_refdup("HEAD", 0, head_sha1, &flag);
	if (branch && starts_with(branch, "refs/heads/"))
		branch += 11;
	if (!branch || is_null_sha1(head_sha1))
		head_commit = NULL;
	else
		head_commit = lookup_commit_or_die(head_sha1, "HEAD");

	git_config(git_merge_config, NULL);

	if (branch_mergeoptions)
		parse_branch_merge_options(branch_mergeoptions);
	argc = parse_options(argc, argv, prefix, builtin_merge_options,
			builtin_merge_usage, 0);
	if (shortlog_len < 0)
		shortlog_len = (merge_log_config > 0) ? merge_log_config : 0;

	if (verbosity < 0 && show_progress == -1)
		show_progress = 0;

	if (abort_current_merge) {
		int nargc = 2;
		const char *nargv[] = {"reset", "--merge", NULL};

		if (!file_exists(git_path("MERGE_HEAD")))
			die(_("There is no merge to abort (MERGE_HEAD missing)."));

		/* Invoke 'git reset --merge' */
		ret = cmd_reset(nargc, nargv, prefix);
		goto done;
	}

	if (read_cache_unmerged())
		die_resolve_conflict("merge");

	if (file_exists(git_path("MERGE_HEAD"))) {
		/*
		 * There is no unmerged entry, don't advise 'git
		 * add/rm <file>', just 'git commit'.
		 */
		if (advice_resolve_conflict)
			die(_("You have not concluded your merge (MERGE_HEAD exists).\n"
				  "Please, commit your changes before you merge."));
		else
			die(_("You have not concluded your merge (MERGE_HEAD exists)."));
	}
	if (file_exists(git_path("CHERRY_PICK_HEAD"))) {
		if (advice_resolve_conflict)
			die(_("You have not concluded your cherry-pick (CHERRY_PICK_HEAD exists).\n"
			    "Please, commit your changes before you merge."));
		else
			die(_("You have not concluded your cherry-pick (CHERRY_PICK_HEAD exists)."));
	}
	resolve_undo_clear();

	if (verbosity < 0)
		show_diffstat = 0;

	if (squash) {
		if (fast_forward == FF_NO)
			die(_("You cannot combine --squash with --no-ff."));
		option_commit = 0;
	}

	if (!argc) {
		if (default_to_upstream)
			argc = setup_with_upstream(&argv);
		else
			die(_("No commit specified and merge.defaultToUpstream not set."));
	} else if (argc == 1 && !strcmp(argv[0], "-")) {
		argv[0] = "@{-1}";
	}

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
		read_empty(remote_head->object.sha1, 0);
		update_ref("initial pull", "HEAD", remote_head->object.sha1,
			   NULL, 0, UPDATE_REFS_DIE_ON_ERR);
		goto done;
	}

	/*
	 * This could be traditional "merge <msg> HEAD <commit>..."  and
	 * the way we can tell it is to see if the second token is HEAD,
	 * but some people might have misused the interface and used a
	 * commit-ish that is the same as HEAD there instead.
	 * Traditional format never would have "-m" so it is an
	 * additional safety measure to check for it.
	 */
	if (!have_message &&
	    is_old_style_invocation(argc, argv, head_commit->object.sha1)) {
		warning("old-style 'git merge <msg> HEAD <commit>' is deprecated.");
		strbuf_addstr(&merge_msg, argv[0]);
		head_arg = argv[1];
		argv += 2;
		argc -= 2;
		remoteheads = collect_parents(head_commit, &head_subsumed,
					      argc, argv, NULL);
	} else {
		/* We are invoked directly as the first-class UI. */
		head_arg = "HEAD";

		/*
		 * All the rest are the commits being merged; prepare
		 * the standard merge summary message to be appended
		 * to the given message.
		 */
		remoteheads = collect_parents(head_commit, &head_subsumed,
					      argc, argv, &merge_msg);
	}

	if (!head_commit || !argc)
		usage_with_options(builtin_merge_usage,
			builtin_merge_options);

	if (verify_signatures) {
		for (p = remoteheads; p; p = p->next) {
			struct commit *commit = p->item;
			char hex[41];
			struct signature_check signature_check;
			memset(&signature_check, 0, sizeof(signature_check));

			check_commit_signature(commit, &signature_check);

			strcpy(hex, find_unique_abbrev(commit->object.sha1, DEFAULT_ABBREV));
			switch (signature_check.result) {
			case 'G':
				break;
			case 'U':
				die(_("Commit %s has an untrusted GPG signature, "
				      "allegedly by %s."), hex, signature_check.signer);
			case 'B':
				die(_("Commit %s has a bad GPG signature "
				      "allegedly by %s."), hex, signature_check.signer);
			default: /* 'N' */
				die(_("Commit %s does not have a GPG signature."), hex);
			}
			if (verbosity >= 0 && signature_check.result == 'G')
				printf(_("Commit %s has a good GPG signature by %s\n"),
				       hex, signature_check.signer);

			signature_check_clear(&signature_check);
		}
	}

	strbuf_addstr(&buf, "merge");
	for (p = remoteheads; p; p = p->next)
		strbuf_addf(&buf, " %s", merge_remote_util(p->item)->name);
	setenv("GIT_REFLOG_ACTION", buf.buf, 0);
	strbuf_reset(&buf);

	for (p = remoteheads; p; p = p->next) {
		struct commit *commit = p->item;
		strbuf_addf(&buf, "GITHEAD_%s",
			    sha1_to_hex(commit->object.sha1));
		setenv(buf.buf, merge_remote_util(commit)->name, 1);
		strbuf_reset(&buf);
		if (fast_forward != FF_ONLY &&
		    merge_remote_util(commit) &&
		    merge_remote_util(commit)->obj &&
		    merge_remote_util(commit)->obj->type == OBJ_TAG)
			fast_forward = FF_NO;
	}

	if (option_edit < 0)
		option_edit = default_edit_option();

	if (!use_strategies) {
		if (!remoteheads)
			; /* already up-to-date */
		else if (!remoteheads->next)
			add_strategies(pull_twohead, DEFAULT_TWOHEAD);
		else
			add_strategies(pull_octopus, DEFAULT_OCTOPUS);
	}

	for (i = 0; i < use_strategies_nr; i++) {
		if (use_strategies[i]->attr & NO_FAST_FORWARD)
			fast_forward = FF_NO;
		if (use_strategies[i]->attr & NO_TRIVIAL)
			allow_trivial = 0;
	}

	if (!remoteheads)
		; /* already up-to-date */
	else if (!remoteheads->next)
		common = get_merge_bases(head_commit, remoteheads->item);
	else {
		struct commit_list *list = remoteheads;
		commit_list_insert(head_commit, &list);
		common = get_octopus_merge_bases(list);
		free(list);
	}

	update_ref("updating ORIG_HEAD", "ORIG_HEAD", head_commit->object.sha1,
		   NULL, 0, UPDATE_REFS_DIE_ON_ERR);

	if (remoteheads && !common)
		; /* No common ancestors found. We need a real merge. */
	else if (!remoteheads ||
		 (!remoteheads->next && !common->next &&
		  common->item == remoteheads->item)) {
		/*
		 * If head can reach all the merge then we are up to date.
		 * but first the most common case of merging one remote.
		 */
		finish_up_to_date("Already up-to-date.");
		goto done;
	} else if (fast_forward != FF_NO && !remoteheads->next &&
			!common->next &&
			!hashcmp(common->item->object.sha1, head_commit->object.sha1)) {
		/* Again the most common case of merging one remote. */
		struct strbuf msg = STRBUF_INIT;
		struct commit *commit;
		char hex[41];

		strcpy(hex, find_unique_abbrev(head_commit->object.sha1, DEFAULT_ABBREV));

		if (verbosity >= 0)
			printf(_("Updating %s..%s\n"),
				hex,
				find_unique_abbrev(remoteheads->item->object.sha1,
				DEFAULT_ABBREV));
		strbuf_addstr(&msg, "Fast-forward");
		if (have_message)
			strbuf_addstr(&msg,
				" (no commit created; -m option ignored)");
		commit = remoteheads->item;
		if (!commit) {
			ret = 1;
			goto done;
		}

		if (checkout_fast_forward(head_commit->object.sha1,
					  commit->object.sha1,
					  overwrite_ignore)) {
			ret = 1;
			goto done;
		}

		finish(head_commit, remoteheads, commit->object.sha1, msg.buf);
		drop_save();
		goto done;
	} else if (!remoteheads->next && common->next)
		;
		/*
		 * We are not doing octopus and not fast-forward.  Need
		 * a real merge.
		 */
	else if (!remoteheads->next && !common->next && option_commit) {
		/*
		 * We are not doing octopus, not fast-forward, and have
		 * only one common.
		 */
		refresh_cache(REFRESH_QUIET);
		if (allow_trivial && fast_forward != FF_ONLY) {
			/* See if it is really trivial. */
			git_committer_info(IDENT_STRICT);
			printf(_("Trying really trivial in-index merge...\n"));
			if (!read_tree_trivial(common->item->object.sha1,
					       head_commit->object.sha1,
					       remoteheads->item->object.sha1)) {
				ret = merge_trivial(head_commit, remoteheads);
				goto done;
			}
			printf(_("Nope.\n"));
		}
	} else {
		/*
		 * An octopus.  If we can reach all the remote we are up
		 * to date.
		 */
		int up_to_date = 1;
		struct commit_list *j;

		for (j = remoteheads; j; j = j->next) {
			struct commit_list *common_one;

			/*
			 * Here we *have* to calculate the individual
			 * merge_bases again, otherwise "git merge HEAD^
			 * HEAD^^" would be missed.
			 */
			common_one = get_merge_bases(head_commit, j->item);
			if (hashcmp(common_one->item->object.sha1,
				j->item->object.sha1)) {
				up_to_date = 0;
				break;
			}
		}
		if (up_to_date) {
			finish_up_to_date("Already up-to-date. Yeeah!");
			goto done;
		}
	}

	if (fast_forward == FF_ONLY)
		die(_("Not possible to fast-forward, aborting."));

	/* We are going to make a new commit. */
	git_committer_info(IDENT_STRICT);

	/*
	 * At this point, we need a real merge.  No matter what strategy
	 * we use, it would operate on the index, possibly affecting the
	 * working tree, and when resolved cleanly, have the desired
	 * tree in the index -- this means that the index must be in
	 * sync with the head commit.  The strategies are responsible
	 * to ensure this.
	 */
	if (use_strategies_nr == 1 ||
	    /*
	     * Stash away the local changes so that we can try more than one.
	     */
	    save_state(stash))
		hashcpy(stash, null_sha1);

	for (i = 0; i < use_strategies_nr; i++) {
		int ret;
		if (i) {
			printf(_("Rewinding the tree to pristine...\n"));
			restore_state(head_commit->object.sha1, stash);
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
					 head_commit, head_arg);
		if (!option_commit && !ret) {
			merge_was_ok = 1;
			/*
			 * This is necessary here just to avoid writing
			 * the tree, but later we will *not* exit with
			 * status code 1 because merge_was_ok is set.
			 */
			ret = 1;
		}

		if (ret) {
			/*
			 * The backend exits with 1 when conflicts are
			 * left to be resolved, with 2 when it does not
			 * handle the given merge at all.
			 */
			if (ret == 1) {
				int cnt = evaluate_result();

				if (best_cnt <= 0 || cnt <= best_cnt) {
					best_strategy = use_strategies[i]->name;
					best_cnt = cnt;
				}
			}
			if (merge_was_ok)
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
		restore_state(head_commit->object.sha1, stash);
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
		restore_state(head_commit->object.sha1, stash);
		printf(_("Using the %s to prepare resolving by hand.\n"),
			best_strategy);
		try_merge_strategy(best_strategy, common, remoteheads,
				   head_commit, head_arg);
	}

	if (squash)
		finish(head_commit, remoteheads, NULL, NULL);
	else
		write_merge_state(remoteheads);

	if (merge_was_ok)
		fprintf(stderr, _("Automatic merge went well; "
			"stopped before committing as requested\n"));
	else
		ret = suggest_conflicts();

done:
	free(branch_to_free);
	return ret;
}