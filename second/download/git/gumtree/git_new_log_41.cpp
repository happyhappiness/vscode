status_printf_ln(s, GIT_COLOR_NORMAL,
				_("%s"
				"Committer: %.*s <%.*s>"),
				ident_shown++ ? "" : "\n",
				(int)(ci.name_end - ci.name_begin), ci.name_begin,
				(int)(ci.mail_end - ci.mail_begin), ci.mail_begin);