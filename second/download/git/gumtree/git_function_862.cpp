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