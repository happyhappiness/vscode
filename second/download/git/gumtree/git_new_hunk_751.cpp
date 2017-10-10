	if (!file_exists(git_path_cherry_pick_head()) &&
	    !file_exists(git_path_revert_head()))
		return error(_("no cherry-pick or revert in progress"));
	return run_command_v_opt(argv, RUN_GIT_CMD);
}

static int commit_staged_changes(struct replay_opts *opts)
{
	int amend = 0;

	if (has_unstaged_changes(1))
		return error(_("cannot rebase: You have unstaged changes."));
	if (!has_uncommitted_changes(0)) {
		const char *cherry_pick_head = git_path("CHERRY_PICK_HEAD");

		if (file_exists(cherry_pick_head) && unlink(cherry_pick_head))
			return error(_("could not remove CHERRY_PICK_HEAD"));
		return 0;
	}

	if (file_exists(rebase_path_amend())) {
		struct strbuf rev = STRBUF_INIT;
		unsigned char head[20], to_amend[20];

		if (get_sha1("HEAD", head))
			return error(_("cannot amend non-existing commit"));
		if (!read_oneliner(&rev, rebase_path_amend(), 0))
			return error(_("invalid file: '%s'"), rebase_path_amend());
		if (get_sha1_hex(rev.buf, to_amend))
			return error(_("invalid contents: '%s'"),
				rebase_path_amend());
		if (hashcmp(head, to_amend))
			return error(_("\nYou have uncommitted changes in your "
				       "working tree. Please, commit them\n"
				       "first and then run 'git rebase "
				       "--continue' again."));

		strbuf_release(&rev);
		amend = 1;
	}

	if (run_git_commit(rebase_path_message(), opts, 1, 1, amend, 0))
		return error(_("could not commit staged changes."));
	unlink(rebase_path_amend());
	return 0;
}

int sequencer_continue(struct replay_opts *opts)
{
	struct todo_list todo_list = TODO_LIST_INIT;
	int res;

	if (read_and_refresh_cache(opts))
		return -1;

	if (is_rebase_i(opts)) {
		if (commit_staged_changes(opts))
			return -1;
	} else if (!file_exists(get_todo_path(opts)))
		return continue_single_pick();
	if (read_populate_opts(opts))
		return -1;
	if ((res = read_populate_todo(&todo_list, opts)))
		goto release_todo_list;

	if (!is_rebase_i(opts)) {
		/* Verify that the conflict has been resolved */
		if (file_exists(git_path_cherry_pick_head()) ||
		    file_exists(git_path_revert_head())) {
			res = continue_single_pick();
			if (res)
				goto release_todo_list;
		}
		if (index_differs_from("HEAD", 0, 0)) {
			res = error_dirty_index(opts);
			goto release_todo_list;
		}
		todo_list.current++;
	} else if (file_exists(rebase_path_stopped_sha())) {
		struct strbuf buf = STRBUF_INIT;
		struct object_id oid;

		if (read_oneliner(&buf, rebase_path_stopped_sha(), 1) &&
		    !get_sha1_committish(buf.buf, oid.hash))
			record_in_rewritten(&oid, peek_command(&todo_list, 0));
		strbuf_release(&buf);
	}

	res = pick_commits(&todo_list, opts);
release_todo_list:
	todo_list_release(&todo_list);
	return res;
}

static int single_pick(struct commit *cmit, struct replay_opts *opts)
{
	setenv(GIT_REFLOG_ACTION, action_name(opts), 0);
	return do_pick_commit(opts->action == REPLAY_PICK ?
		TODO_PICK : TODO_REVERT, cmit, opts, 0);
}

int sequencer_pick_revisions(struct replay_opts *opts)
{
	struct todo_list todo_list = TODO_LIST_INIT;
	unsigned char sha1[20];
