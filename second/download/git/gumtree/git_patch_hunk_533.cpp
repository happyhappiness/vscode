 		opts->record_origin = git_config_bool_or_int(key, value, &error_flag);
 	else if (!strcmp(key, "options.allow-ff"))
 		opts->allow_ff = git_config_bool_or_int(key, value, &error_flag);
 	else if (!strcmp(key, "options.mainline"))
 		opts->mainline = git_config_int(key, value);
 	else if (!strcmp(key, "options.strategy"))
-		git_config_string(&opts->strategy, key, value);
+		git_config_string_dup(&opts->strategy, key, value);
 	else if (!strcmp(key, "options.gpg-sign"))
-		git_config_string(&opts->gpg_sign, key, value);
+		git_config_string_dup(&opts->gpg_sign, key, value);
 	else if (!strcmp(key, "options.strategy-option")) {
 		ALLOC_GROW(opts->xopts, opts->xopts_nr + 1, opts->xopts_alloc);
 		opts->xopts[opts->xopts_nr++] = xstrdup(value);
 	} else
-		return error(_("Invalid key: %s"), key);
+		return error(_("invalid key: %s"), key);
 
 	if (!error_flag)
-		return error(_("Invalid value for %s: %s"), key, value);
+		return error(_("invalid value for %s: %s"), key, value);
 
 	return 0;
 }
 
-static void read_populate_opts(struct replay_opts **opts_ptr)
+static int read_populate_opts(struct replay_opts *opts)
 {
+	if (is_rebase_i(opts)) {
+		struct strbuf buf = STRBUF_INIT;
+
+		if (read_oneliner(&buf, rebase_path_gpg_sign_opt(), 1)) {
+			if (!starts_with(buf.buf, "-S"))
+				strbuf_reset(&buf);
+			else {
+				free(opts->gpg_sign);
+				opts->gpg_sign = xstrdup(buf.buf + 2);
+			}
+		}
+		strbuf_release(&buf);
+
+		return 0;
+	}
+
 	if (!file_exists(git_path_opts_file()))
-		return;
-	if (git_config_from_file(populate_opts_cb, git_path_opts_file(), *opts_ptr) < 0)
-		die(_("Malformed options sheet: %s"), git_path_opts_file());
+		return 0;
+	/*
+	 * The function git_parse_source(), called from git_config_from_file(),
+	 * may die() in case of a syntactically incorrect file. We do not care
+	 * about this case, though, because we wrote that file ourselves, so we
+	 * are pretty certain that it is syntactically correct.
+	 */
+	if (git_config_from_file(populate_opts_cb, git_path_opts_file(), opts) < 0)
+		return error(_("malformed options sheet: '%s'"),
+			git_path_opts_file());
+	return 0;
 }
 
-static void walk_revs_populate_todo(struct commit_list **todo_list,
+static int walk_revs_populate_todo(struct todo_list *todo_list,
 				struct replay_opts *opts)
 {
+	enum todo_command command = opts->action == REPLAY_PICK ?
+		TODO_PICK : TODO_REVERT;
+	const char *command_string = todo_command_strings[command];
 	struct commit *commit;
-	struct commit_list **next;
 
-	prepare_revs(opts);
+	if (prepare_revs(opts))
+		return -1;
 
-	next = todo_list;
-	while ((commit = get_revision(opts->revs)))
-		next = commit_list_append(commit, next);
+	while ((commit = get_revision(opts->revs))) {
+		struct todo_item *item = append_new_todo(todo_list);
+		const char *commit_buffer = get_commit_buffer(commit, NULL);
+		const char *subject;
+		int subject_len;
+
+		item->command = command;
+		item->commit = commit;
+		item->arg = NULL;
+		item->arg_len = 0;
+		item->offset_in_buf = todo_list->buf.len;
+		subject_len = find_commit_subject(commit_buffer, &subject);
+		strbuf_addf(&todo_list->buf, "%s %s %.*s\n", command_string,
+			short_commit_name(commit), subject_len, subject);
+		unuse_commit_buffer(commit, commit_buffer);
+	}
+	return 0;
 }
 
 static int create_seq_dir(void)
 {
 	if (file_exists(git_path_seq_dir())) {
 		error(_("a cherry-pick or revert is already in progress"));
 		advise(_("try \"git cherry-pick (--continue | --quit | --abort)\""));
 		return -1;
 	}
 	else if (mkdir(git_path_seq_dir(), 0777) < 0)
-		die_errno(_("Could not create sequencer directory %s"),
-			  git_path_seq_dir());
+		return error_errno(_("could not create sequencer directory '%s'"),
+				   git_path_seq_dir());
 	return 0;
 }
 
-static void save_head(const char *head)
+static int save_head(const char *head)
 {
 	static struct lock_file head_lock;
 	struct strbuf buf = STRBUF_INIT;
 	int fd;
 
-	fd = hold_lock_file_for_update(&head_lock, git_path_head_file(), LOCK_DIE_ON_ERROR);
+	fd = hold_lock_file_for_update(&head_lock, git_path_head_file(), 0);
+	if (fd < 0) {
+		rollback_lock_file(&head_lock);
+		return error_errno(_("could not lock HEAD"));
+	}
 	strbuf_addf(&buf, "%s\n", head);
-	if (write_in_full(fd, buf.buf, buf.len) < 0)
-		die_errno(_("Could not write to %s"), git_path_head_file());
-	if (commit_lock_file(&head_lock) < 0)
-		die(_("Error wrapping up %s."), git_path_head_file());
+	if (write_in_full(fd, buf.buf, buf.len) < 0) {
+		rollback_lock_file(&head_lock);
+		return error_errno(_("could not write to '%s'"),
+				   git_path_head_file());
+	}
+	if (commit_lock_file(&head_lock) < 0) {
+		rollback_lock_file(&head_lock);
+		return error(_("failed to finalize '%s'."), git_path_head_file());
+	}
+	return 0;
 }
 
 static int reset_for_rollback(const unsigned char *sha1)
 {
 	const char *argv[4];	/* reset --merge <arg> + NULL */
 	argv[0] = "reset";
