int sequencer_pick_revisions(struct replay_opts *opts)
{
	struct commit_list *todo_list = NULL;
	unsigned char sha1[20];
	int i;

	if (opts->subcommand == REPLAY_NONE)
		assert(opts->revs);

	read_and_refresh_cache(opts);

	/*
	 * Decide what to do depending on the arguments; a fresh
	 * cherry-pick should be handled differently from an existing
	 * one that is being continued
	 */
	if (opts->subcommand == REPLAY_REMOVE_STATE) {
		remove_sequencer_state();
		return 0;
	}
	if (opts->subcommand == REPLAY_ROLLBACK)
		return sequencer_rollback(opts);
	if (opts->subcommand == REPLAY_CONTINUE)
		return sequencer_continue(opts);

	for (i = 0; i < opts->revs->pending.nr; i++) {
		unsigned char sha1[20];
		const char *name = opts->revs->pending.objects[i].name;

		/* This happens when using --stdin. */
		if (!strlen(name))
			continue;

		if (!get_sha1(name, sha1)) {
			if (!lookup_commit_reference_gently(sha1, 1)) {
				enum object_type type = sha1_object_info(sha1, NULL);
				die(_("%s: can't cherry-pick a %s"), name, typename(type));
			}
		} else
			die(_("%s: bad revision"), name);
	}

	/*
	 * If we were called as "git cherry-pick <commit>", just
	 * cherry-pick/revert it, set CHERRY_PICK_HEAD /
	 * REVERT_HEAD, and don't touch the sequencer state.
	 * This means it is possible to cherry-pick in the middle
	 * of a cherry-pick sequence.
	 */
	if (opts->revs->cmdline.nr == 1 &&
	    opts->revs->cmdline.rev->whence == REV_CMD_REV &&
	    opts->revs->no_walk &&
	    !opts->revs->cmdline.rev->flags) {
		struct commit *cmit;
		if (prepare_revision_walk(opts->revs))
			die(_("revision walk setup failed"));
		cmit = get_revision(opts->revs);
		if (!cmit || get_revision(opts->revs))
			die("BUG: expected exactly one commit from walk");
		return single_pick(cmit, opts);
	}

	/*
	 * Start a new cherry-pick/ revert sequence; but
	 * first, make sure that an existing one isn't in
	 * progress
	 */

	walk_revs_populate_todo(&todo_list, opts);
	if (create_seq_dir() < 0)
		return -1;
	if (get_sha1("HEAD", sha1)) {
		if (opts->action == REPLAY_REVERT)
			return error(_("Can't revert as initial commit"));
		return error(_("Can't cherry-pick into empty head"));
	}
	save_head(sha1_to_hex(sha1));
	save_opts(opts);
	return pick_commits(todo_list, opts);
}