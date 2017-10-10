	if (opt->cleanup_mode != CLEANUP_NONE)
		strbuf_stripspace(buf, opt->cleanup_mode == CLEANUP_ALL);

	if (!opt->message_given && !buf->len)
		die(_("no tag message?"));

	strbuf_insert(buf, 0, header.buf, header.len);
	strbuf_release(&header);

	if (build_tag_object(buf, opt->sign, result) < 0) {
		if (path)
			fprintf(stderr, _("The tag message has been left in %s\n"),
				path);
		exit(128);
