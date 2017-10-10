			strbuf_addstr(&msgbuf, cherry_picked_prefix);
			strbuf_addstr(&msgbuf, oid_to_hex(&commit->object.oid));
			strbuf_addstr(&msgbuf, ")\n");
		}
	}

	if (!opts->strategy || !strcmp(opts->strategy, "recursive") || opts->action == REPLAY_REVERT) {
		res = do_recursive_merge(base, next, base_label, next_label,
					 head, &msgbuf, opts);
		if (res < 0)
			return res;
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
		update_ref(NULL, "CHERRY_PICK_HEAD", commit->object.oid.hash, NULL,
			   REF_NODEREF, UPDATE_REFS_DIE_ON_ERR);
	if (opts->action == REPLAY_REVERT && ((opts->no_commit && res == 0) || res == 1))
		update_ref(NULL, "REVERT_HEAD", commit->object.oid.hash, NULL,
			   REF_NODEREF, UPDATE_REFS_DIE_ON_ERR);

	if (res) {
		error(opts->action == REPLAY_REVERT
		      ? _("could not revert %s... %s")
		      : _("could not apply %s... %s"),
		      find_unique_abbrev(commit->object.oid.hash, DEFAULT_ABBREV),
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

static void prepare_revs(struct replay_opts *opts)
{
	/*
	 * picking (but not reverting) ranges (but not individual revisions)
	 * should be done in reverse
	 */
	if (opts->action == REPLAY_PICK && !opts->revs->no_walk)
		opts->revs->reverse ^= 1;

	if (prepare_revision_walk(opts->revs))
		die(_("revision walk setup failed"));

	if (!opts->revs->commits)
		die(_("empty commit set passed"));
}

static void read_and_refresh_cache(struct replay_opts *opts)
{
	static struct lock_file index_lock;
	int index_fd = hold_locked_index(&index_lock, 0);
	if (read_index_preload(&the_index, NULL) < 0)
		die(_("git %s: failed to read the index"), action_name(opts));
	refresh_index(&the_index, REFRESH_QUIET|REFRESH_UNMERGED, NULL, NULL, NULL);
	if (the_index.cache_changed && index_fd >= 0) {
		if (write_locked_index(&the_index, &index_lock, COMMIT_LOCK))
			die(_("git %s: failed to refresh the index"), action_name(opts));
	}
	rollback_lock_file(&index_lock);
}

static int format_todo(struct strbuf *buf, struct commit_list *todo_list,
		struct replay_opts *opts)
{
	struct commit_list *cur = NULL;
	const char *sha1_abbrev = NULL;
	const char *action_str = opts->action == REPLAY_REVERT ? "revert" : "pick";
	const char *subject;
	int subject_len;

	for (cur = todo_list; cur; cur = cur->next) {
		const char *commit_buffer = get_commit_buffer(cur->item, NULL);
		sha1_abbrev = find_unique_abbrev(cur->item->object.oid.hash, DEFAULT_ABBREV);
		subject_len = find_commit_subject(commit_buffer, &subject);
		strbuf_addf(buf, "%s %s %.*s\n", action_str, sha1_abbrev,
			subject_len, subject);
		unuse_commit_buffer(cur->item, commit_buffer);
	}
	return 0;
}

static struct commit *parse_insn_line(char *bol, char *eol, struct replay_opts *opts)
{
	unsigned char commit_sha1[20];
	enum replay_action action;
	char *end_of_object_name;
	int saved, status, padding;

	if (starts_with(bol, "pick")) {
		action = REPLAY_PICK;
		bol += strlen("pick");
	} else if (starts_with(bol, "revert")) {
		action = REPLAY_REVERT;
		bol += strlen("revert");
	} else
		return NULL;

	/* Eat up extra spaces/ tabs before object name */
	padding = strspn(bol, " \t");
	if (!padding)
		return NULL;
	bol += padding;

	end_of_object_name = bol + strcspn(bol, " \t\n");
	saved = *end_of_object_name;
	*end_of_object_name = '\0';
	status = get_sha1(bol, commit_sha1);
	*end_of_object_name = saved;

	/*
	 * Verify that the action matches up with the one in
	 * opts; we don't support arbitrary instructions
	 */
	if (action != opts->action) {
		if (action == REPLAY_REVERT)
		      error((opts->action == REPLAY_REVERT)
			    ? _("Cannot revert during another revert.")
			    : _("Cannot revert during a cherry-pick."));
		else
		      error((opts->action == REPLAY_REVERT)
			    ? _("Cannot cherry-pick during a revert.")
			    : _("Cannot cherry-pick during another cherry-pick."));
		return NULL;
	}

	if (status < 0)
		return NULL;

	return lookup_commit_reference(commit_sha1);
}

static int parse_insn_buffer(char *buf, struct commit_list **todo_list,
			struct replay_opts *opts)
{
	struct commit_list **next = todo_list;
	struct commit *commit;
	char *p = buf;
	int i;

	for (i = 1; *p; i++) {
		char *eol = strchrnul(p, '\n');
		commit = parse_insn_line(p, eol, opts);
		if (!commit)
			return error(_("Could not parse line %d."), i);
		next = commit_list_append(commit, next);
		p = *eol ? eol + 1 : eol;
	}
	if (!*todo_list)
		return error(_("No commits parsed."));
	return 0;
}

static void read_populate_todo(struct commit_list **todo_list,
			struct replay_opts *opts)
{
	struct strbuf buf = STRBUF_INIT;
	int fd, res;

	fd = open(git_path_todo_file(), O_RDONLY);
	if (fd < 0)
		die_errno(_("Could not open %s"), git_path_todo_file());
	if (strbuf_read(&buf, fd, 0) < 0) {
		close(fd);
		strbuf_release(&buf);
		die(_("Could not read %s."), git_path_todo_file());
	}
	close(fd);

	res = parse_insn_buffer(buf.buf, todo_list, opts);
	strbuf_release(&buf);
	if (res)
		die(_("Unusable instruction sheet: %s"), git_path_todo_file());
}

static int populate_opts_cb(const char *key, const char *value, void *data)
{
	struct replay_opts *opts = data;
	int error_flag = 1;
