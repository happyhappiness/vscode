							"options.strategy-option",
							opts->xopts[i], "^$", 0);
	}
	return res;
}

static int make_patch(struct commit *commit, struct replay_opts *opts)
{
	struct strbuf buf = STRBUF_INIT;
	struct rev_info log_tree_opt;
	const char *subject, *p;
	int res = 0;

	p = short_commit_name(commit);
	if (write_message(p, strlen(p), rebase_path_stopped_sha(), 1) < 0)
		return -1;

	strbuf_addf(&buf, "%s/patch", get_dir(opts));
	memset(&log_tree_opt, 0, sizeof(log_tree_opt));
	init_revisions(&log_tree_opt, NULL);
	log_tree_opt.abbrev = 0;
	log_tree_opt.diff = 1;
	log_tree_opt.diffopt.output_format = DIFF_FORMAT_PATCH;
	log_tree_opt.disable_stdin = 1;
	log_tree_opt.no_commit_id = 1;
	log_tree_opt.diffopt.file = fopen(buf.buf, "w");
	log_tree_opt.diffopt.use_color = GIT_COLOR_NEVER;
	if (!log_tree_opt.diffopt.file)
		res |= error_errno(_("could not open '%s'"), buf.buf);
	else {
		res |= log_tree_commit(&log_tree_opt, commit);
		fclose(log_tree_opt.diffopt.file);
	}
	strbuf_reset(&buf);

	strbuf_addf(&buf, "%s/message", get_dir(opts));
	if (!file_exists(buf.buf)) {
		const char *commit_buffer = get_commit_buffer(commit, NULL);
		find_commit_subject(commit_buffer, &subject);
		res |= write_message(subject, strlen(subject), buf.buf, 1);
		unuse_commit_buffer(commit, commit_buffer);
	}
	strbuf_release(&buf);

	return res;
}

static int intend_to_amend(void)
{
	unsigned char head[20];
	char *p;

	if (get_sha1("HEAD", head))
		return error(_("cannot read HEAD"));

	p = sha1_to_hex(head);
	return write_message(p, strlen(p), rebase_path_amend(), 1);
}

static int error_with_patch(struct commit *commit,
	const char *subject, int subject_len,
	struct replay_opts *opts, int exit_code, int to_amend)
{
	if (make_patch(commit, opts))
		return -1;

	if (to_amend) {
		if (intend_to_amend())
			return -1;

		fprintf(stderr, "You can amend the commit now, with\n"
			"\n"
			"  git commit --amend %s\n"
			"\n"
			"Once you are satisfied with your changes, run\n"
			"\n"
			"  git rebase --continue\n", gpg_sign_opt_quoted(opts));
	} else if (exit_code)
		fprintf(stderr, "Could not apply %s... %.*s\n",
			short_commit_name(commit), subject_len, subject);

	return exit_code;
}

static int error_failed_squash(struct commit *commit,
	struct replay_opts *opts, int subject_len, const char *subject)
{
	if (rename(rebase_path_squash_msg(), rebase_path_message()))
		return error(_("could not rename '%s' to '%s'"),
			rebase_path_squash_msg(), rebase_path_message());
	unlink(rebase_path_fixup_msg());
	unlink(git_path("MERGE_MSG"));
	if (copy_file(git_path("MERGE_MSG"), rebase_path_message(), 0666))
		return error(_("could not copy '%s' to '%s'"),
			     rebase_path_message(), git_path("MERGE_MSG"));
	return error_with_patch(commit, subject, subject_len, opts, 1, 0);
}

static int do_exec(const char *command_line)
{
	const char *child_argv[] = { NULL, NULL };
	int dirty, status;

	fprintf(stderr, "Executing: %s\n", command_line);
	child_argv[0] = command_line;
	status = run_command_v_opt(child_argv, RUN_USING_SHELL);

	/* force re-reading of the cache */
	if (discard_cache() < 0 || read_cache() < 0)
		return error(_("could not read index"));

	dirty = require_clean_work_tree("rebase", NULL, 1, 1);

	if (status) {
		warning(_("execution failed: %s\n%s"
			  "You can fix the problem, and then run\n"
			  "\n"
			  "  git rebase --continue\n"
			  "\n"),
			command_line,
			dirty ? N_("and made changes to the index and/or the "
				"working tree\n") : "");
		if (status == 127)
			/* command not found */
			status = 1;
	} else if (dirty) {
		warning(_("execution succeeded: %s\nbut "
			  "left changes to the index and/or the working tree\n"
			  "Commit or stash your changes, and then run\n"
			  "\n"
			  "  git rebase --continue\n"
			  "\n"), command_line);
		status = 1;
	}

	return status;
}

static int is_final_fixup(struct todo_list *todo_list)
{
	int i = todo_list->current;

	if (!is_fixup(todo_list->items[i].command))
		return 0;

	while (++i < todo_list->nr)
		if (is_fixup(todo_list->items[i].command))
			return 0;
		else if (!is_noop(todo_list->items[i].command))
			break;
	return 1;
}

static enum todo_command peek_command(struct todo_list *todo_list, int offset)
{
	int i;

	for (i = todo_list->current + offset; i < todo_list->nr; i++)
		if (!is_noop(todo_list->items[i].command))
			return todo_list->items[i].command;

	return -1;
}

static int apply_autostash(struct replay_opts *opts)
{
	struct strbuf stash_sha1 = STRBUF_INIT;
	struct child_process child = CHILD_PROCESS_INIT;
	int ret = 0;

	if (!read_oneliner(&stash_sha1, rebase_path_autostash(), 1)) {
		strbuf_release(&stash_sha1);
		return 0;
	}
	strbuf_trim(&stash_sha1);

	child.git_cmd = 1;
	argv_array_push(&child.args, "stash");
	argv_array_push(&child.args, "apply");
	argv_array_push(&child.args, stash_sha1.buf);
	if (!run_command(&child))
		printf(_("Applied autostash."));
	else {
		struct child_process store = CHILD_PROCESS_INIT;

		store.git_cmd = 1;
		argv_array_push(&store.args, "stash");
		argv_array_push(&store.args, "store");
		argv_array_push(&store.args, "-m");
		argv_array_push(&store.args, "autostash");
		argv_array_push(&store.args, "-q");
		argv_array_push(&store.args, stash_sha1.buf);
		if (run_command(&store))
			ret = error(_("cannot store %s"), stash_sha1.buf);
		else
			printf(_("Applying autostash resulted in conflicts.\n"
				"Your changes are safe in the stash.\n"
				"You can run \"git stash pop\" or"
				" \"git stash drop\" at any time.\n"));
	}

	strbuf_release(&stash_sha1);
	return ret;
}

static const char *reflog_message(struct replay_opts *opts,
	const char *sub_action, const char *fmt, ...)
{
	va_list ap;
	static struct strbuf buf = STRBUF_INIT;

	va_start(ap, fmt);
	strbuf_reset(&buf);
	strbuf_addstr(&buf, action_name(opts));
	if (sub_action)
		strbuf_addf(&buf, " (%s)", sub_action);
	if (fmt) {
		strbuf_addstr(&buf, ": ");
		strbuf_vaddf(&buf, fmt, ap);
	}
	va_end(ap);

	return buf.buf;
}

static int pick_commits(struct todo_list *todo_list, struct replay_opts *opts)
{
	int res = 0;

	setenv(GIT_REFLOG_ACTION, action_name(opts), 0);
	if (opts->allow_ff)
		assert(!(opts->signoff || opts->no_commit ||
				opts->record_origin || opts->edit));
	if (read_and_refresh_cache(opts))
		return -1;

	while (todo_list->current < todo_list->nr) {
		struct todo_item *item = todo_list->items + todo_list->current;
		if (save_todo(todo_list, opts))
			return -1;
		if (is_rebase_i(opts)) {
			if (item->command != TODO_COMMENT) {
				FILE *f = fopen(rebase_path_msgnum(), "w");

				todo_list->done_nr++;

				if (f) {
					fprintf(f, "%d\n", todo_list->done_nr);
					fclose(f);
				}
				fprintf(stderr, "Rebasing (%d/%d)%s",
					todo_list->done_nr,
					todo_list->total_nr,
					opts->verbose ? "\n" : "\r");
			}
			unlink(rebase_path_message());
			unlink(rebase_path_author_script());
			unlink(rebase_path_stopped_sha());
			unlink(rebase_path_amend());
		}
		if (item->command <= TODO_SQUASH) {
			if (is_rebase_i(opts))
				setenv("GIT_REFLOG_ACTION", reflog_message(opts,
					command_to_string(item->command), NULL),
					1);
			res = do_pick_commit(item->command, item->commit,
					opts, is_final_fixup(todo_list));
			if (is_rebase_i(opts) && res < 0) {
				/* Reschedule */
				todo_list->current--;
				if (save_todo(todo_list, opts))
					return -1;
			}
			if (item->command == TODO_EDIT) {
				struct commit *commit = item->commit;
				if (!res)
					warning(_("stopped at %s... %.*s"),
						short_commit_name(commit),
						item->arg_len, item->arg);
				return error_with_patch(commit,
					item->arg, item->arg_len, opts, res,
					!res);
			}
			if (is_rebase_i(opts) && !res)
				record_in_rewritten(&item->commit->object.oid,
					peek_command(todo_list, 1));
			if (res && is_fixup(item->command)) {
				if (res == 1)
					intend_to_amend();
				return error_failed_squash(item->commit, opts,
					item->arg_len, item->arg);
			} else if (res && is_rebase_i(opts))
				return res | error_with_patch(item->commit,
					item->arg, item->arg_len, opts, res,
					item->command == TODO_REWORD);
		} else if (item->command == TODO_EXEC) {
			char *end_of_arg = (char *)(item->arg + item->arg_len);
			int saved = *end_of_arg;

			*end_of_arg = '\0';
			res = do_exec(item->arg);
			*end_of_arg = saved;
		} else if (!is_noop(item->command))
			return error(_("unknown command %d"), item->command);

		todo_list->current++;
		if (res)
			return res;
	}

	if (is_rebase_i(opts)) {
		struct strbuf head_ref = STRBUF_INIT, buf = STRBUF_INIT;
		struct stat st;

		/* Stopped in the middle, as planned? */
		if (todo_list->current < todo_list->nr)
			return 0;

		if (read_oneliner(&head_ref, rebase_path_head_name(), 0) &&
				starts_with(head_ref.buf, "refs/")) {
			const char *msg;
			unsigned char head[20], orig[20];
			int res;

			if (get_sha1("HEAD", head)) {
				res = error(_("cannot read HEAD"));
cleanup_head_ref:
				strbuf_release(&head_ref);
				strbuf_release(&buf);
				return res;
			}
			if (!read_oneliner(&buf, rebase_path_orig_head(), 0) ||
					get_sha1_hex(buf.buf, orig)) {
				res = error(_("could not read orig-head"));
				goto cleanup_head_ref;
			}
			if (!read_oneliner(&buf, rebase_path_onto(), 0)) {
				res = error(_("could not read 'onto'"));
				goto cleanup_head_ref;
			}
			msg = reflog_message(opts, "finish", "%s onto %s",
				head_ref.buf, buf.buf);
			if (update_ref(msg, head_ref.buf, head, orig,
					REF_NODEREF, UPDATE_REFS_MSG_ON_ERR)) {
				res = error(_("could not update %s"),
					head_ref.buf);
				goto cleanup_head_ref;
			}
			msg = reflog_message(opts, "finish", "returning to %s",
				head_ref.buf);
			if (create_symref("HEAD", head_ref.buf, msg)) {
				res = error(_("could not update HEAD to %s"),
					head_ref.buf);
				goto cleanup_head_ref;
			}
			strbuf_reset(&buf);
		}

		if (opts->verbose) {
			struct rev_info log_tree_opt;
			struct object_id orig, head;

			memset(&log_tree_opt, 0, sizeof(log_tree_opt));
			init_revisions(&log_tree_opt, NULL);
			log_tree_opt.diff = 1;
			log_tree_opt.diffopt.output_format =
				DIFF_FORMAT_DIFFSTAT;
			log_tree_opt.disable_stdin = 1;

			if (read_oneliner(&buf, rebase_path_orig_head(), 0) &&
			    !get_sha1(buf.buf, orig.hash) &&
			    !get_sha1("HEAD", head.hash)) {
				diff_tree_sha1(orig.hash, head.hash,
					       "", &log_tree_opt.diffopt);
				log_tree_diff_flush(&log_tree_opt);
			}
		}
		flush_rewritten_pending();
		if (!stat(rebase_path_rewritten_list(), &st) &&
				st.st_size > 0) {
			struct child_process child = CHILD_PROCESS_INIT;
			const char *post_rewrite_hook =
				find_hook("post-rewrite");

			child.in = open(rebase_path_rewritten_list(), O_RDONLY);
			child.git_cmd = 1;
			argv_array_push(&child.args, "notes");
			argv_array_push(&child.args, "copy");
			argv_array_push(&child.args, "--for-rewrite=rebase");
			/* we don't care if this copying failed */
			run_command(&child);

			if (post_rewrite_hook) {
				struct child_process hook = CHILD_PROCESS_INIT;

				hook.in = open(rebase_path_rewritten_list(),
					O_RDONLY);
				hook.stdout_to_stderr = 1;
				argv_array_push(&hook.args, post_rewrite_hook);
				argv_array_push(&hook.args, "rebase");
				/* we don't care if this hook failed */
				run_command(&hook);
			}
		}
		apply_autostash(opts);

		fprintf(stderr, "Successfully rebased and updated %s.\n",
			head_ref.buf);

		strbuf_release(&buf);
		strbuf_release(&head_ref);
	}

	/*
	 * Sequence of picks finished successfully; cleanup by
	 * removing the .git/sequencer directory
	 */
	return sequencer_remove_state(opts);
}
