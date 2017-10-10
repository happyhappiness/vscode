status_printf_ln(s, GIT_COLOR_NORMAL,
				_("%s"
				"Committer: %s"),
				ident_shown++ ? "" : "\n",
				committer_ident.buf);