	if (is_null_sha1(sha1)) {
		error(_("cannot abort from a branch yet to be born"));
		goto fail;
	}
	if (reset_for_rollback(sha1))
		goto fail;
	remove_sequencer_state();
	strbuf_release(&buf);
	return 0;
fail:
	strbuf_release(&buf);
	return -1;
}

static void save_todo(struct commit_list *todo_list, struct replay_opts *opts)
{
	static struct lock_file todo_lock;
	struct strbuf buf = STRBUF_INIT;
	int fd;

	fd = hold_lock_file_for_update(&todo_lock, git_path_todo_file(), LOCK_DIE_ON_ERROR);
	if (format_todo(&buf, todo_list, opts) < 0)
		die(_("Could not format %s."), git_path_todo_file());
	if (write_in_full(fd, buf.buf, buf.len) < 0) {
		strbuf_release(&buf);
		die_errno(_("Could not write to %s"), git_path_todo_file());
	}
	if (commit_lock_file(&todo_lock) < 0) {
		strbuf_release(&buf);
		die(_("Error wrapping up %s."), git_path_todo_file());
	}
	strbuf_release(&buf);
}

static void save_opts(struct replay_opts *opts)
{
	const char *opts_file = git_path_opts_file();

	if (opts->no_commit)
		git_config_set_in_file(opts_file, "options.no-commit", "true");
	if (opts->edit)
		git_config_set_in_file(opts_file, "options.edit", "true");
	if (opts->signoff)
		git_config_set_in_file(opts_file, "options.signoff", "true");
	if (opts->record_origin)
		git_config_set_in_file(opts_file, "options.record-origin", "true");
	if (opts->allow_ff)
		git_config_set_in_file(opts_file, "options.allow-ff", "true");
	if (opts->mainline) {
		struct strbuf buf = STRBUF_INIT;
		strbuf_addf(&buf, "%d", opts->mainline);
		git_config_set_in_file(opts_file, "options.mainline", buf.buf);
		strbuf_release(&buf);
	}
	if (opts->strategy)
		git_config_set_in_file(opts_file, "options.strategy", opts->strategy);
	if (opts->gpg_sign)
		git_config_set_in_file(opts_file, "options.gpg-sign", opts->gpg_sign);
	if (opts->xopts) {
		int i;
		for (i = 0; i < opts->xopts_nr; i++)
			git_config_set_multivar_in_file(opts_file,
							"options.strategy-option",
							opts->xopts[i], "^$", 0);
	}
}

static int pick_commits(struct commit_list *todo_list, struct replay_opts *opts)
{
	struct commit_list *cur;
	int res;

	setenv(GIT_REFLOG_ACTION, action_name(opts), 0);
	if (opts->allow_ff)
		assert(!(opts->signoff || opts->no_commit ||
				opts->record_origin || opts->edit));
	read_and_refresh_cache(opts);

	for (cur = todo_list; cur; cur = cur->next) {
		save_todo(cur, opts);
		res = do_pick_commit(cur->item, opts);
		if (res)
			return res;
	}

	/*
	 * Sequence of picks finished successfully; cleanup by
	 * removing the .git/sequencer directory
	 */
	remove_sequencer_state();
	return 0;
}

static int continue_single_pick(void)
{
	const char *argv[] = { "commit", NULL };

	if (!file_exists(git_path_cherry_pick_head()) &&
	    !file_exists(git_path_revert_head()))
		return error(_("no cherry-pick or revert in progress"));
	return run_command_v_opt(argv, RUN_GIT_CMD);
}

static int sequencer_continue(struct replay_opts *opts)
{
	struct commit_list *todo_list = NULL;

	if (!file_exists(git_path_todo_file()))
		return continue_single_pick();
	read_populate_opts(&opts);
	read_populate_todo(&todo_list, opts);

	/* Verify that the conflict has been resolved */
	if (file_exists(git_path_cherry_pick_head()) ||
	    file_exists(git_path_revert_head())) {
		int ret = continue_single_pick();
		if (ret)
			return ret;
	}
	if (index_differs_from("HEAD", 0))
		return error_dirty_index(opts);
	todo_list = todo_list->next;
	return pick_commits(todo_list, opts);
}

static int single_pick(struct commit *cmit, struct replay_opts *opts)
{
	setenv(GIT_REFLOG_ACTION, action_name(opts), 0);
	return do_pick_commit(cmit, opts);
}

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
