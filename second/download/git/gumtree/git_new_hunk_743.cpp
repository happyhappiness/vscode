
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
			cleanup_commit_message = 1;
			msg_file = rebase_path_fixup_msg();
		} else {
			const char *dest = git_path("SQUASH_MSG");
			unlink(dest);
			if (copy_file(dest, rebase_path_squash_msg(), 0666))
				return error(_("could not rename '%s' to '%s'"),
					     rebase_path_squash_msg(), dest);
			unlink(git_path("MERGE_MSG"));
			msg_file = dest;
			edit = 1;
		}
	}

	if (is_rebase_i(opts) && write_author_script(msg.message) < 0)
		res = -1;
	else if (!opts->strategy || !strcmp(opts->strategy, "recursive") || command == TODO_REVERT) {
		res = do_recursive_merge(base, next, base_label, next_label,
					 head, &msgbuf, opts);
		if (res < 0)
			return res;
		res |= write_message(msgbuf.buf, msgbuf.len,
				     git_path_merge_msg(), 0);
