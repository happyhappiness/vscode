status_printf_ln(s, GIT_COLOR_NORMAL,
				_("%s"
				"Author:    %s"),
				ident_shown++ ? "" : "\n",
				author_ident->buf);