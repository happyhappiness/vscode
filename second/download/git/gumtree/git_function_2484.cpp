static int checkout_paths(const struct checkout_opts *opts,
			  const char *revision)
{
	int pos;
	struct checkout state;
	static char *ps_matched;
	unsigned char rev[20];
	struct commit *head;
	int errs = 0;
	struct lock_file *lock_file;

	if (opts->track != BRANCH_TRACK_UNSPECIFIED)
		die(_("'%s' cannot be used with updating paths"), "--track");

	if (opts->new_branch_log)
		die(_("'%s' cannot be used with updating paths"), "-l");

	if (opts->force && opts->patch_mode)
		die(_("'%s' cannot be used with updating paths"), "-f");

	if (opts->force_detach)
		die(_("'%s' cannot be used with updating paths"), "--detach");

	if (opts->merge && opts->patch_mode)
		die(_("'%s' cannot be used with %s"), "--merge", "--patch");

	if (opts->force && opts->merge)
		die(_("'%s' cannot be used with %s"), "-f", "-m");

	if (opts->new_branch)
		die(_("Cannot update paths and switch to branch '%s' at the same time."),
		    opts->new_branch);

	if (opts->patch_mode)
		return run_add_interactive(revision, "--patch=checkout",
					   &opts->pathspec);

	lock_file = xcalloc(1, sizeof(struct lock_file));

	hold_locked_index(lock_file, 1);
	if (read_cache_preload(&opts->pathspec) < 0)
		return error(_("corrupt index file"));

	if (opts->source_tree)
		read_tree_some(opts->source_tree, &opts->pathspec);

	ps_matched = xcalloc(opts->pathspec.nr, 1);

	/*
	 * Make sure all pathspecs participated in locating the paths
	 * to be checked out.
	 */
	for (pos = 0; pos < active_nr; pos++) {
		struct cache_entry *ce = active_cache[pos];
		ce->ce_flags &= ~CE_MATCHED;
		if (!opts->ignore_skipworktree && ce_skip_worktree(ce))
			continue;
		if (opts->source_tree && !(ce->ce_flags & CE_UPDATE))
			/*
			 * "git checkout tree-ish -- path", but this entry
			 * is in the original index; it will not be checked
			 * out to the working tree and it does not matter
			 * if pathspec matched this entry.  We will not do
			 * anything to this entry at all.
			 */
			continue;
		/*
		 * Either this entry came from the tree-ish we are
		 * checking the paths out of, or we are checking out
		 * of the index.
		 *
		 * If it comes from the tree-ish, we already know it
		 * matches the pathspec and could just stamp
		 * CE_MATCHED to it from update_some(). But we still
		 * need ps_matched and read_tree_recursive (and
		 * eventually tree_entry_interesting) cannot fill
		 * ps_matched yet. Once it can, we can avoid calling
		 * match_pathspec() for _all_ entries when
		 * opts->source_tree != NULL.
		 */
		if (ce_path_match(ce, &opts->pathspec, ps_matched))
			ce->ce_flags |= CE_MATCHED;
	}

	if (report_path_error(ps_matched, &opts->pathspec, opts->prefix)) {
		free(ps_matched);
		return 1;
	}
	free(ps_matched);

	/* "checkout -m path" to recreate conflicted state */
	if (opts->merge)
		unmerge_marked_index(&the_index);

	/* Any unmerged paths? */
	for (pos = 0; pos < active_nr; pos++) {
		const struct cache_entry *ce = active_cache[pos];
		if (ce->ce_flags & CE_MATCHED) {
			if (!ce_stage(ce))
				continue;
			if (opts->force) {
				warning(_("path '%s' is unmerged"), ce->name);
			} else if (opts->writeout_stage) {
				errs |= check_stage(opts->writeout_stage, ce, pos);
			} else if (opts->merge) {
				errs |= check_stages((1<<2) | (1<<3), ce, pos);
			} else {
				errs = 1;
				error(_("path '%s' is unmerged"), ce->name);
			}
			pos = skip_same_name(ce, pos) - 1;
		}
	}
	if (errs)
		return 1;

	/* Now we are committed to check them out */
	memset(&state, 0, sizeof(state));
	state.force = 1;
	state.refresh_cache = 1;
	state.istate = &the_index;
	for (pos = 0; pos < active_nr; pos++) {
		struct cache_entry *ce = active_cache[pos];
		if (ce->ce_flags & CE_MATCHED) {
			if (!ce_stage(ce)) {
				errs |= checkout_entry(ce, &state, NULL);
				continue;
			}
			if (opts->writeout_stage)
				errs |= checkout_stage(opts->writeout_stage, ce, pos, &state);
			else if (opts->merge)
				errs |= checkout_merged(pos, &state);
			pos = skip_same_name(ce, pos) - 1;
		}
	}

	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));

	read_ref_full("HEAD", 0, rev, NULL);
	head = lookup_commit_reference_gently(rev, 1);

	errs |= post_checkout_hook(head, head, 0);
	return errs;
}