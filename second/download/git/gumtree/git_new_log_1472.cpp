status_printf_ln(s, color(WT_STATUS_HEADER, s),
				 s->commit_template
				 ? _("Initial commit")
				 : _("No commits yet"));