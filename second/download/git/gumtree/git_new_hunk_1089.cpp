		return error(_("no cherry-pick or revert in progress"));
	return run_command_v_opt(argv, RUN_GIT_CMD);
}

static int commit_staged_changes(struct replay_opts *opts)
{
	unsigned int flags = ALLOW_EMPTY | EDIT_MSG;

	if (has_unstaged_changes(1))
		return error(_("cannot rebase: You have unstaged changes."));
	if (!has_uncommitted_changes(0)) {
		const char *cherry_pick_head = git_path_cherry_pick_head();

		if (file_exists(cherry_pick_head) && unlink(cherry_pick_head))
			return error(_("could not remove CHERRY_PICK_HEAD"));
		return 0;
	}

