		} else
			skip_prefix(branch_name, "refs/heads/", &branch_name);
		status_printf(s, color(WT_STATUS_HEADER, s), "%s", "");
		status_printf_more(s, branch_status_color, "%s", on_what);
		status_printf_more(s, branch_color, "%s\n", branch_name);
		if (!s->is_initial)
			wt_longstatus_print_tracking(s);
	}

	wt_longstatus_print_state(s, &state);
	free(state.branch);
	free(state.onto);
	free(state.detached_from);

	if (s->is_initial) {
		status_printf_ln(s, color(WT_STATUS_HEADER, s), "%s", "");
		status_printf_ln(s, color(WT_STATUS_HEADER, s), _("Initial commit"));
		status_printf_ln(s, color(WT_STATUS_HEADER, s), "%s", "");
	}

	wt_longstatus_print_updated(s);
	wt_longstatus_print_unmerged(s);
	wt_longstatus_print_changed(s);
	if (s->submodule_summary &&
	    (!s->ignore_submodule_arg ||
	     strcmp(s->ignore_submodule_arg, "all"))) {
		wt_longstatus_print_submodule_summary(s, 0);  /* staged */
		wt_longstatus_print_submodule_summary(s, 1);  /* unstaged */
	}
	if (s->show_untracked_files) {
		wt_longstatus_print_other(s, &s->untracked, _("Untracked files"), "add");
		if (s->show_ignored_files)
			wt_longstatus_print_other(s, &s->ignored, _("Ignored files"), "add -f");
		if (advice_status_u_option && 2000 < s->untracked_in_ms) {
			status_printf_ln(s, GIT_COLOR_NORMAL, "%s", "");
			status_printf_ln(s, GIT_COLOR_NORMAL,
					 _("It took %.2f seconds to enumerate untracked files. 'status -uno'\n"
					   "may speed it up, but you have to be careful not to forget to add\n"
					   "new files yourself (see 'git help status')."),
