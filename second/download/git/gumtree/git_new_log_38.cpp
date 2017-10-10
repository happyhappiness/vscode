status_printf_ln(s, GIT_COLOR_NORMAL,
				_("%s"
				"Author:    %.*s <%.*s>"),
				ident_shown++ ? "" : "\n",
				(int)(ai.name_end - ai.name_begin), ai.name_begin,
				(int)(ai.mail_end - ai.mail_begin), ai.mail_begin);