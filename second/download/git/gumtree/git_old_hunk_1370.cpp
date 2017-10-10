		/* write the template message before editing: */
		path = git_pathdup("TAG_EDITMSG");
		fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		if (fd < 0)
			die_errno(_("could not create file '%s'"), path);

		if (!is_null_sha1(prev)) {
			write_tag_body(fd, prev);
		} else {
			struct strbuf buf = STRBUF_INIT;
			strbuf_addch(&buf, '\n');
			if (opt->cleanup_mode == CLEANUP_ALL)
				strbuf_commented_addf(&buf, _(tag_template), tag, comment_line_char);
