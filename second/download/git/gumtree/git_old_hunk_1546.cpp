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
