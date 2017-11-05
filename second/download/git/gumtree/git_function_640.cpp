static int update_squash_messages(enum todo_command command,
		struct commit *commit, struct replay_opts *opts)
{
	struct strbuf buf = STRBUF_INIT;
	int count, res;
	const char *message, *body;

	if (file_exists(rebase_path_squash_msg())) {
		struct strbuf header = STRBUF_INIT;
		char *eol, *p;

		if (strbuf_read_file(&buf, rebase_path_squash_msg(), 2048) <= 0)
			return error(_("could not read '%s'"),
				rebase_path_squash_msg());

		p = buf.buf + 1;
		eol = strchrnul(buf.buf, '\n');
		if (buf.buf[0] != comment_line_char ||
		    (p += strcspn(p, "0123456789\n")) == eol)
			return error(_("unexpected 1st line of squash message:"
				       "\n\n\t%.*s"),
				     (int)(eol - buf.buf), buf.buf);
		count = strtol(p, NULL, 10);

		if (count < 1)
			return error(_("invalid 1st line of squash message:\n"
				       "\n\t%.*s"),
				     (int)(eol - buf.buf), buf.buf);

		strbuf_addf(&header, "%c ", comment_line_char);
		strbuf_addf(&header,
			    _("This is a combination of %d commits."), ++count);
		strbuf_splice(&buf, 0, eol - buf.buf, header.buf, header.len);
		strbuf_release(&header);
	} else {
		unsigned char head[20];
		struct commit *head_commit;
		const char *head_message, *body;

		if (get_sha1("HEAD", head))
			return error(_("need a HEAD to fixup"));
		if (!(head_commit = lookup_commit_reference(head)))
			return error(_("could not read HEAD"));
		if (!(head_message = get_commit_buffer(head_commit, NULL)))
			return error(_("could not read HEAD's commit message"));

		find_commit_subject(head_message, &body);
		if (write_message(body, strlen(body),
				  rebase_path_fixup_msg(), 0)) {
			unuse_commit_buffer(head_commit, head_message);
			return error(_("cannot write '%s'"),
				     rebase_path_fixup_msg());
		}

		count = 2;
		strbuf_addf(&buf, "%c ", comment_line_char);
		strbuf_addf(&buf, _("This is a combination of %d commits."),
			    count);
		strbuf_addf(&buf, "\n%c ", comment_line_char);
		strbuf_addstr(&buf, _("This is the 1st commit message:"));
		strbuf_addstr(&buf, "\n\n");
		strbuf_addstr(&buf, body);

		unuse_commit_buffer(head_commit, head_message);
	}

	if (!(message = get_commit_buffer(commit, NULL)))
		return error(_("could not read commit message of %s"),
			     oid_to_hex(&commit->object.oid));
	find_commit_subject(message, &body);

	if (command == TODO_SQUASH) {
		unlink(rebase_path_fixup_msg());
		strbuf_addf(&buf, "\n%c ", comment_line_char);
		strbuf_addf(&buf, _("This is the commit message #%d:"), count);
		strbuf_addstr(&buf, "\n\n");
		strbuf_addstr(&buf, body);
	} else if (command == TODO_FIXUP) {
		strbuf_addf(&buf, "\n%c ", comment_line_char);
		strbuf_addf(&buf, _("The commit message #%d will be skipped:"),
			    count);
		strbuf_addstr(&buf, "\n\n");
		strbuf_add_commented_lines(&buf, body, strlen(body));
	} else
		return error(_("unknown command: %d"), command);
	unuse_commit_buffer(commit, message);

	res = write_message(buf.buf, buf.len, rebase_path_squash_msg(), 0);
	strbuf_release(&buf);
	return res;
}