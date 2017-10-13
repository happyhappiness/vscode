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