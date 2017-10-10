			strbuf_addstr(&msgbuf, cherry_picked_prefix);
			strbuf_addstr(&msgbuf, oid_to_hex(&commit->object.oid));
			strbuf_addstr(&msgbuf, ")\n");
		}
	}

	if (!opts->strategy || !strcmp(opts->strategy, "recursive") || command == TODO_REVERT) {
		res = do_recursive_merge(base, next, base_label, next_label,
					 head, &msgbuf, opts);
		if (res < 0)
			return res;
		res |= write_message(msgbuf.buf, msgbuf.len,
				     git_path_merge_msg(), 0);
	} else {
		struct commit_list *common = NULL;
		struct commit_list *remotes = NULL;

		res = write_message(msgbuf.buf, msgbuf.len,
				    git_path_merge_msg(), 0);

		commit_list_insert(base, &common);
		commit_list_insert(next, &remotes);
		res |= try_merge_command(opts->strategy,
					 opts->xopts_nr, (const char **)opts->xopts,
					common, sha1_to_hex(head), remotes);
		free_commit_list(common);
		free_commit_list(remotes);
	}
	strbuf_release(&msgbuf);

	/*
	 * If the merge was clean or if it failed due to conflict, we write
	 * CHERRY_PICK_HEAD for the subsequent invocation of commit to use.
	 * However, if the merge did not even start, then we don't want to
	 * write it at all.
	 */
	if (command == TODO_PICK && !opts->no_commit && (res == 0 || res == 1) &&
	    update_ref(NULL, "CHERRY_PICK_HEAD", commit->object.oid.hash, NULL,
		       REF_NODEREF, UPDATE_REFS_MSG_ON_ERR))
		res = -1;
	if (command == TODO_REVERT && ((opts->no_commit && res == 0) || res == 1) &&
	    update_ref(NULL, "REVERT_HEAD", commit->object.oid.hash, NULL,
		       REF_NODEREF, UPDATE_REFS_MSG_ON_ERR))
		res = -1;

	if (res) {
		error(command == TODO_REVERT
		      ? _("could not revert %s... %s")
		      : _("could not apply %s... %s"),
		      short_commit_name(commit), msg.subject);
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
		res = run_git_commit(opts->edit ? NULL : git_path_merge_msg(),
				     opts, allow, opts->edit, 0, 0);

leave:
	free_message(commit, &msg);

	return res;
}

static int prepare_revs(struct replay_opts *opts)
{
	/*
	 * picking (but not reverting) ranges (but not individual revisions)
	 * should be done in reverse
	 */
	if (opts->action == REPLAY_PICK && !opts->revs->no_walk)
		opts->revs->reverse ^= 1;

	if (prepare_revision_walk(opts->revs))
		return error(_("revision walk setup failed"));

	if (!opts->revs->commits)
		return error(_("empty commit set passed"));
	return 0;
}

static int read_and_refresh_cache(struct replay_opts *opts)
{
	static struct lock_file index_lock;
	int index_fd = hold_locked_index(&index_lock, 0);
	if (read_index_preload(&the_index, NULL) < 0) {
		rollback_lock_file(&index_lock);
		return error(_("git %s: failed to read the index"),
			_(action_name(opts)));
	}
	refresh_index(&the_index, REFRESH_QUIET|REFRESH_UNMERGED, NULL, NULL, NULL);
	if (the_index.cache_changed && index_fd >= 0) {
		if (write_locked_index(&the_index, &index_lock, COMMIT_LOCK)) {
			rollback_lock_file(&index_lock);
			return error(_("git %s: failed to refresh the index"),
				_(action_name(opts)));
		}
	}
	rollback_lock_file(&index_lock);
	return 0;
}

struct todo_item {
	enum todo_command command;
	struct commit *commit;
	const char *arg;
	int arg_len;
	size_t offset_in_buf;
};

struct todo_list {
	struct strbuf buf;
	struct todo_item *items;
	int nr, alloc, current;
};

#define TODO_LIST_INIT { STRBUF_INIT }

static void todo_list_release(struct todo_list *todo_list)
{
	strbuf_release(&todo_list->buf);
	free(todo_list->items);
	todo_list->items = NULL;
	todo_list->nr = todo_list->alloc = 0;
}

static struct todo_item *append_new_todo(struct todo_list *todo_list)
{
	ALLOC_GROW(todo_list->items, todo_list->nr + 1, todo_list->alloc);
	return todo_list->items + todo_list->nr++;
}

static int parse_insn_line(struct todo_item *item, const char *bol, char *eol)
{
	unsigned char commit_sha1[20];
	char *end_of_object_name;
	int i, saved, status, padding;

	/* left-trim */
	bol += strspn(bol, " \t");

	for (i = 0; i < ARRAY_SIZE(todo_command_strings); i++)
		if (skip_prefix(bol, todo_command_strings[i], &bol)) {
			item->command = i;
			break;
		}
	if (i >= ARRAY_SIZE(todo_command_strings))
		return -1;

	/* Eat up extra spaces/ tabs before object name */
	padding = strspn(bol, " \t");
	if (!padding)
		return -1;
	bol += padding;

	end_of_object_name = (char *) bol + strcspn(bol, " \t\n");
	saved = *end_of_object_name;
	*end_of_object_name = '\0';
	status = get_sha1(bol, commit_sha1);
	*end_of_object_name = saved;

	item->arg = end_of_object_name + strspn(end_of_object_name, " \t");
	item->arg_len = (int)(eol - item->arg);

	if (status < 0)
		return -1;

	item->commit = lookup_commit_reference(commit_sha1);
	return !item->commit;
}

static int parse_insn_buffer(char *buf, struct todo_list *todo_list)
{
	struct todo_item *item;
	char *p = buf, *next_p;
	int i, res = 0;

	for (i = 1; *p; i++, p = next_p) {
		char *eol = strchrnul(p, '\n');

		next_p = *eol ? eol + 1 /* skip LF */ : eol;

		if (p != eol && eol[-1] == '\r')
			eol--; /* strip Carriage Return */

		item = append_new_todo(todo_list);
		item->offset_in_buf = p - todo_list->buf.buf;
		if (parse_insn_line(item, p, eol)) {
			res = error(_("invalid line %d: %.*s"),
				i, (int)(eol - p), p);
			item->command = -1;
		}
	}
	if (!todo_list->nr)
		return error(_("no commits parsed."));
	return res;
}

static int read_populate_todo(struct todo_list *todo_list,
			struct replay_opts *opts)
{
	const char *todo_file = get_todo_path(opts);
	int fd, res;

	strbuf_reset(&todo_list->buf);
	fd = open(todo_file, O_RDONLY);
	if (fd < 0)
		return error_errno(_("could not open '%s'"), todo_file);
	if (strbuf_read(&todo_list->buf, fd, 0) < 0) {
		close(fd);
		return error(_("could not read '%s'."), todo_file);
	}
	close(fd);

	res = parse_insn_buffer(todo_list->buf.buf, todo_list);
	if (res)
		return error(_("unusable instruction sheet: '%s'"), todo_file);

	if (!is_rebase_i(opts)) {
		enum todo_command valid =
			opts->action == REPLAY_PICK ? TODO_PICK : TODO_REVERT;
		int i;

		for (i = 0; i < todo_list->nr; i++)
			if (valid == todo_list->items[i].command)
				continue;
			else if (valid == TODO_PICK)
				return error(_("cannot cherry-pick during a revert."));
			else
				return error(_("cannot revert during a cherry-pick."));
	}

	return 0;
}

static int git_config_string_dup(char **dest,
				 const char *var, const char *value)
{
	if (!value)
		return config_error_nonbool(var);
	free(*dest);
	*dest = xstrdup(value);
	return 0;
}

static int populate_opts_cb(const char *key, const char *value, void *data)
{
	struct replay_opts *opts = data;
	int error_flag = 1;
