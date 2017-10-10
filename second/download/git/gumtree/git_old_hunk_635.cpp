	if (get_sha1("HEAD", sha1) && (opts->action == REPLAY_REVERT))
		return error(_("can't revert as initial commit"));
	if (save_head(sha1_to_hex(sha1)))
		return -1;
	if (save_opts(opts))
		return -1;
	res = pick_commits(&todo_list, opts);
	todo_list_release(&todo_list);
	return res;
}

void append_signoff(struct strbuf *msgbuf, int ignore_footer, unsigned flag)
