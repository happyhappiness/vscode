				  " yourself if you want to.\n"
				  "An empty message aborts the commit.\n"), comment_line_char);
		if (only_include_assumed)
			status_printf_ln(s, GIT_COLOR_NORMAL,
					"%s", only_include_assumed);

		ai_tmp = cut_ident_timestamp_part(author_ident->buf);
		ci_tmp = cut_ident_timestamp_part(committer_ident.buf);
		if (strcmp(author_ident->buf, committer_ident.buf))
			status_printf_ln(s, GIT_COLOR_NORMAL,
				_("%s"
				"Author:    %s"),
				ident_shown++ ? "" : "\n",
				author_ident->buf);

		if (!committer_ident_sufficiently_given())
			status_printf_ln(s, GIT_COLOR_NORMAL,
				_("%s"
				"Committer: %s"),
				ident_shown++ ? "" : "\n",
				committer_ident.buf);

		if (ident_shown)
			status_printf_ln(s, GIT_COLOR_NORMAL, "");

		saved_color_setting = s->use_color;
		s->use_color = 0;
		commitable = run_status(s->fp, index_file, prefix, 1, s);
		s->use_color = saved_color_setting;

		*ai_tmp = ' ';
		*ci_tmp = ' ';
	} else {
		unsigned char sha1[20];
		const char *parent = "HEAD";

		if (!active_nr && read_cache() < 0)
			die(_("Cannot read index"));
