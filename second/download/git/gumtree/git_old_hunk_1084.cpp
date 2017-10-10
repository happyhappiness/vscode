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
