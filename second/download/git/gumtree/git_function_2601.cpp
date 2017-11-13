static int do_pick_commit(struct commit *commit, struct replay_opts *opts)
{
	unsigned char head[20];
	struct commit *base, *next, *parent;
	const char *base_label, *next_label;
	struct commit_message msg = { NULL, NULL, NULL, NULL };
	struct strbuf msgbuf = STRBUF_INIT;
	int res, unborn = 0, allow;

	if (opts->no_commit) {
		/*
		 * We do not intend to commit immediately.  We just want to
		 * merge the differences in, so let's compute the tree
		 * that represents the "current" state for merge-recursive
		 * to work on.
		 */
		if (write_cache_as_tree(head, 0, NULL))
			die (_("Your index file is unmerged."));
	} else {
		unborn = get_sha1("HEAD", head);
		if (unborn)
			hashcpy(head, EMPTY_TREE_SHA1_BIN);
		if (index_differs_from(unborn ? EMPTY_TREE_SHA1_HEX : "HEAD", 0))
			return error_dirty_index(opts);
	}
	discard_cache();

	if (!commit->parents) {
		parent = NULL;
	}
	else if (commit->parents->next) {
		/* Reverting or cherry-picking a merge commit */
		int cnt;
		struct commit_list *p;

		if (!opts->mainline)
			return error(_("Commit %s is a merge but no -m option was given."),
				sha1_to_hex(commit->object.sha1));

		for (cnt = 1, p = commit->parents;
		     cnt != opts->mainline && p;
		     cnt++)
			p = p->next;
		if (cnt != opts->mainline || !p)
			return error(_("Commit %s does not have parent %d"),
				sha1_to_hex(commit->object.sha1), opts->mainline);
		parent = p->item;
	} else if (0 < opts->mainline)
		return error(_("Mainline was specified but commit %s is not a merge."),
			sha1_to_hex(commit->object.sha1));
	else
		parent = commit->parents->item;

	if (opts->allow_ff &&
	    ((parent && !hashcmp(parent->object.sha1, head)) ||
	     (!parent && unborn)))
		return fast_forward_to(commit->object.sha1, head, unborn, opts);

	if (parent && parse_commit(parent) < 0)
		/* TRANSLATORS: The first %s will be "revert" or
		   "cherry-pick", the second %s a SHA1 */
		return error(_("%s: cannot parse parent commit %s"),
			action_name(opts), sha1_to_hex(parent->object.sha1));

	if (get_message(commit, &msg) != 0)
		return error(_("Cannot get commit message for %s"),
			sha1_to_hex(commit->object.sha1));

	/*
	 * "commit" is an existing commit.  We would want to apply
	 * the difference it introduces since its first parent "prev"
	 * on top of the current HEAD if we are cherry-pick.  Or the
	 * reverse of it if we are revert.
	 */

	if (opts->action == REPLAY_REVERT) {
		base = commit;
		base_label = msg.label;
		next = parent;
		next_label = msg.parent_label;
		strbuf_addstr(&msgbuf, "Revert \"");
		strbuf_addstr(&msgbuf, msg.subject);
		strbuf_addstr(&msgbuf, "\"\n\nThis reverts commit ");
		strbuf_addstr(&msgbuf, sha1_to_hex(commit->object.sha1));

		if (commit->parents && commit->parents->next) {
			strbuf_addstr(&msgbuf, ", reversing\nchanges made to ");
			strbuf_addstr(&msgbuf, sha1_to_hex(parent->object.sha1));
		}
		strbuf_addstr(&msgbuf, ".\n");
	} else {
		const char *p;

		base = parent;
		base_label = msg.parent_label;
		next = commit;
		next_label = msg.label;

		/*
		 * Append the commit log message to msgbuf; it starts
		 * after the tree, parent, author, committer
		 * information followed by "\n\n".
		 */
		p = strstr(msg.message, "\n\n");
		if (p) {
			p += 2;
			strbuf_addstr(&msgbuf, p);
		}

		if (opts->record_origin) {
			if (!has_conforming_footer(&msgbuf, NULL, 0))
				strbuf_addch(&msgbuf, '\n');
			strbuf_addstr(&msgbuf, cherry_picked_prefix);
			strbuf_addstr(&msgbuf, sha1_to_hex(commit->object.sha1));
			strbuf_addstr(&msgbuf, ")\n");
		}
	}

	if (!opts->strategy || !strcmp(opts->strategy, "recursive") || opts->action == REPLAY_REVERT) {
		res = do_recursive_merge(base, next, base_label, next_label,
					 head, &msgbuf, opts);
		write_message(&msgbuf, git_path_merge_msg());
	} else {
		struct commit_list *common = NULL;
		struct commit_list *remotes = NULL;

		write_message(&msgbuf, git_path_merge_msg());

		commit_list_insert(base, &common);
		commit_list_insert(next, &remotes);
		res = try_merge_command(opts->strategy, opts->xopts_nr, opts->xopts,
					common, sha1_to_hex(head), remotes);
		free_commit_list(common);
		free_commit_list(remotes);
	}

	/*
	 * If the merge was clean or if it failed due to conflict, we write
	 * CHERRY_PICK_HEAD for the subsequent invocation of commit to use.
	 * However, if the merge did not even start, then we don't want to
	 * write it at all.
	 */
	if (opts->action == REPLAY_PICK && !opts->no_commit && (res == 0 || res == 1))
		update_ref(NULL, "CHERRY_PICK_HEAD", commit->object.sha1, NULL,
			   REF_NODEREF, UPDATE_REFS_DIE_ON_ERR);
	if (opts->action == REPLAY_REVERT && ((opts->no_commit && res == 0) || res == 1))
		update_ref(NULL, "REVERT_HEAD", commit->object.sha1, NULL,
			   REF_NODEREF, UPDATE_REFS_DIE_ON_ERR);

	if (res) {
		error(opts->action == REPLAY_REVERT
		      ? _("could not revert %s... %s")
		      : _("could not apply %s... %s"),
		      find_unique_abbrev(commit->object.sha1, DEFAULT_ABBREV),
		      msg.subject);
		print_advice(res == 1, opts);
		rerere(opts->allow_rerere_auto);
		goto leave;
	}

	allow = allow_empty(opts, commit);
	if (allow < 0) {
		res = allow;
		goto leave;
	}
	if (!opts->no_commit)
		res = run_git_commit(git_path_merge_msg(), opts, allow);

leave:
	free_message(commit, &msg);

	return res;
}