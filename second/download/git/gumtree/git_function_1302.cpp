int cmd_pull(int argc, const char **argv, const char *prefix)
{
	const char *repo, **refspecs;
	struct oid_array merge_heads = OID_ARRAY_INIT;
	struct object_id orig_head, curr_head;
	struct object_id rebase_fork_point;
	int autostash;

	if (!getenv("GIT_REFLOG_ACTION"))
		set_reflog_message(argc, argv);

	argc = parse_options(argc, argv, prefix, pull_options, pull_usage, 0);

	parse_repo_refspecs(argc, argv, &repo, &refspecs);

	if (!opt_ff)
		opt_ff = xstrdup_or_null(config_get_ff());

	if (opt_rebase < 0)
		opt_rebase = config_get_rebase();

	git_config(git_pull_config, NULL);

	if (read_cache_unmerged())
		die_resolve_conflict("pull");

	if (file_exists(git_path_merge_head()))
		die_conclude_merge();

	if (get_oid("HEAD", &orig_head))
		oidclr(&orig_head);

	if (!opt_rebase && opt_autostash != -1)
		die(_("--[no-]autostash option is only valid with --rebase."));

	autostash = config_autostash;
	if (opt_rebase) {
		if (opt_autostash != -1)
			autostash = opt_autostash;

		if (is_null_oid(&orig_head) && !is_cache_unborn())
			die(_("Updating an unborn branch with changes added to the index."));

		if (!autostash)
			require_clean_work_tree(N_("pull with rebase"),
				_("please commit or stash them."), 1, 0);

		if (get_rebase_fork_point(&rebase_fork_point, repo, *refspecs))
			oidclr(&rebase_fork_point);
	}

	if (run_fetch(repo, refspecs))
		return 1;

	if (opt_dry_run)
		return 0;

	if (get_oid("HEAD", &curr_head))
		oidclr(&curr_head);

	if (!is_null_oid(&orig_head) && !is_null_oid(&curr_head) &&
			oidcmp(&orig_head, &curr_head)) {
		/*
		 * The fetch involved updating the current branch.
		 *
		 * The working tree and the index file are still based on
		 * orig_head commit, but we are merging into curr_head.
		 * Update the working tree to match curr_head.
		 */

		warning(_("fetch updated the current branch head.\n"
			"fast-forwarding your working tree from\n"
			"commit %s."), oid_to_hex(&orig_head));

		if (checkout_fast_forward(&orig_head, &curr_head, 0))
			die(_("Cannot fast-forward your working tree.\n"
				"After making sure that you saved anything precious from\n"
				"$ git diff %s\n"
				"output, run\n"
				"$ git reset --hard\n"
				"to recover."), oid_to_hex(&orig_head));
	}

	get_merge_heads(&merge_heads);

	if (!merge_heads.nr)
		die_no_merge_candidates(repo, refspecs);

	if (is_null_oid(&orig_head)) {
		if (merge_heads.nr > 1)
			die(_("Cannot merge multiple branches into empty head."));
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