static int do_pick_commit(enum todo_command command, struct commit *commit,
		struct replay_opts *opts, int final_fixup)
{
	int edit = opts->edit, cleanup_commit_message = 0;
	const char *msg_file = edit ? NULL : git_path_merge_msg();
	unsigned char head[20];
	struct commit *base, *next, *parent;
	const char *base_label, *next_label;
	struct commit_message msg = { NULL, NULL, NULL, NULL };
	struct strbuf msgbuf = STRBUF_INIT;
	int res, unborn = 0, amend = 0, allow = 0;

	if (opts->no_commit) {
		/*
		 * We do not intend to commit immediately.  We just want to
		 * merge the differences in, so let's compute the tree
		 * that represents the "current" state for merge-recursive
		 * to work on.
		 */
		if (write_cache_as_tree(head, 0, NULL))
			return error(_("your index file is unmerged."));
	} else {
		unborn = get_sha1("HEAD", head);
		if (unborn)
			hashcpy(head, EMPTY_TREE_SHA1_BIN);
		if (index_differs_from(unborn ? EMPTY_TREE_SHA1_HEX : "HEAD", 0, 0))
			return error_dirty_index(opts);
	}
	discard_cache();

	if (!commit->parents)
		parent = NULL;
	else if (commit->parents->next) {
		/* Reverting or cherry-picking a merge commit */
		int cnt;
		struct commit_list *p;

		if (!opts->mainline)
			return error(_("commit %s is a merge but no -m option was given."),
				oid_to_hex(&commit->object.oid));

		for (cnt = 1, p = commit->parents;
		     cnt != opts->mainline && p;
		     cnt++)
			p = p->next;
		if (cnt != opts->mainline || !p)
			return error(_("commit %s does not have parent %d"),
				oid_to_hex(&commit->object.oid), opts->mainline);
		parent = p->item;
	} else if (0 < opts->mainline)
		return error(_("mainline was specified but commit %s is not a merge."),
			oid_to_hex(&commit->object.oid));
	else
		parent = commit->parents->item;

	if (get_message(commit, &msg) != 0)
		return error(_("cannot get commit message for %s"),
			oid_to_hex(&commit->object.oid));

	if (opts->allow_ff && !is_fixup(command) &&
	    ((parent && !hashcmp(parent->object.oid.hash, head)) ||
	     (!parent && unborn))) {
		if (is_rebase_i(opts))
			write_author_script(msg.message);
		res = fast_forward_to(commit->object.oid.hash, head, unborn,
			opts);
		if (res || command != TODO_REWORD)
			goto leave;
		edit = amend = 1;
		msg_file = NULL;
		goto fast_forward_edit;
	}
	if (parent && parse_commit(parent) < 0)
		/* TRANSLATORS: The first %s will be a "todo" command like
		   "revert" or "pick", the second %s a SHA1. */
		return error(_("%s: cannot parse parent commit %s"),
			command_to_string(command),
			oid_to_hex(&parent->object.oid));

	/*
	 * "commit" is an existing commit.  We would want to apply
	 * the difference it introduces since its first parent "prev"
	 * on top of the current HEAD if we are cherry-pick.  Or the
	 * reverse of it if we are revert.
	 */

	if (command == TODO_REVERT) {
		base = commit;
		base_label = msg.label;
		next = parent;
		next_label = msg.parent_label;
		strbuf_addstr(&msgbuf, "Revert \"");
		strbuf_addstr(&msgbuf, msg.subject);
		strbuf_addstr(&msgbuf, "\"\n\nThis reverts commit ");
		strbuf_addstr(&msgbuf, oid_to_hex(&commit->object.oid));

		if (commit->parents && commit->parents->next) {
			strbuf_addstr(&msgbuf, ", reversing\nchanges made to ");
			strbuf_addstr(&msgbuf, oid_to_hex(&parent->object.oid));
		}
		strbuf_addstr(&msgbuf, ".\n");
	} else {
		const char *p;

		base = parent;
		base_label = msg.parent_label;
		next = commit;
		next_label = msg.label;

		/* Append the commit log message to msgbuf. */
		if (find_commit_subject(msg.message, &p))
			strbuf_addstr(&msgbuf, p);

		if (opts->record_origin) {
			if (!has_conforming_footer(&msgbuf, NULL, 0))
				strbuf_addch(&msgbuf, '\n');
			strbuf_addstr(&msgbuf, cherry_picked_prefix);
			strbuf_addstr(&msgbuf, oid_to_hex(&commit->object.oid));
			strbuf_addstr(&msgbuf, ")\n");
		}
	}

	if (command == TODO_REWORD)
		edit = 1;
	else if (is_fixup(command)) {
		if (update_squash_messages(command, commit, opts))
			return -1;
		amend = 1;
		if (!final_fixup)
			msg_file = rebase_path_squash_msg();
		else if (file_exists(rebase_path_fixup_msg())) {