				_("%s"
				"Committer: %.*s <%.*s>"),
				ident_shown++ ? "" : "\n",
				(int)(ci.name_end - ci.name_begin), ci.name_begin,
				(int)(ci.mail_end - ci.mail_begin), ci.mail_begin);

		status_printf_ln(s, GIT_COLOR_NORMAL, "%s", ""); /* Add new line for clarity */

		saved_color_setting = s->use_color;
		s->use_color = 0;
		commitable = run_status(s->fp, index_file, prefix, 1, s);
		s->use_color = saved_color_setting;
	} else {
