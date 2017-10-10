	}
	if (s->show_untracked_files) {
		wt_status_print_other(s, &s->untracked, _("Untracked files"), "add");
		if (s->show_ignored_files)
			wt_status_print_other(s, &s->ignored, _("Ignored files"), "add -f");
		if (advice_status_u_option && 2000 < s->untracked_in_ms) {
			status_printf_ln(s, GIT_COLOR_NORMAL, "");
			status_printf_ln(s, GIT_COLOR_NORMAL,
					 _("It took %.2f seconds to enumerate untracked files. 'status -uno'\n"
					   "may speed it up, but you have to be careful not to forget to add\n"
					   "new files yourself (see 'git help status')."),
					 s->untracked_in_ms / 1000.0);
		}
