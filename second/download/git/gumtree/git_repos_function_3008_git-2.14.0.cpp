int sequencer_pick_revisions(struct replay_opts *opts)
{
	struct todo_list todo_list = TODO_LIST_INIT;
	struct object_id oid;
	int i, res;

	assert(opts->revs);
	if (read_and_refresh_cache(opts))
		return -1;

	for (i = 0; i < opts->revs->pending.nr; i++) {
		struct object_id oid;
		const char *name = opts->revs->pending.objects[i].name;

		/* This happens when using --stdin. */
		if (!strlen(name))
			continue;

		if (!get_oid(name, &oid)) {
			if (!lookup_commit_reference_gently(&oid, 1)) {
				enum object_type type = sha1_object_info(oid.hash, NULL);
				return error(_("%s: can't cherry-pick a %s"),
					name, typename(type));
			}
		} else
			return error(_("%s: bad revision"), name);
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
			return error(_("revision walk setup failed"));
		cmit = get_revision(opts->revs);
		if (!cmit || get_revision(opts->revs))
			return error("BUG: expected exactly one commit from walk");
		return single_pick(cmit, opts);
	}

	/*
	 * Start a new cherry-pick/ revert sequence; but
	 * first, make sure that an existing one isn't in
	 * progress
	 */

	if (walk_revs_populate_todo(&todo_list, opts) ||
			create_seq_dir() < 0)
		return -1;
	if (get_oid("HEAD", &oid) && (opts->action == REPLAY_REVERT))
		return error(_("can't revert as initial commit"));
	if (save_head(oid_to_hex(&oid)))
		return -1;
	if (save_opts(opts))
		return -1;
	update_abort_safety_file();
	res = pick_commits(&todo_list, opts);
	todo_list_release(&todo_list);
	return res;
}