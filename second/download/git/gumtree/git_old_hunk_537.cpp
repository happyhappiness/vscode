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
	if (get_sha1("HEAD", sha1) && (opts->action == REPLAY_REVERT))
		return error(_("Can't revert as initial commit"));
	save_head(sha1_to_hex(sha1));
	save_opts(opts);
	return pick_commits(todo_list, opts);
}

void append_signoff(struct strbuf *msgbuf, int ignore_footer, unsigned flag)
{
	unsigned no_dup_sob = flag & APPEND_SIGNOFF_DEDUP;
	struct strbuf sob = STRBUF_INIT;
