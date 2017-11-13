static void wt_longstatus_print(struct wt_status *s)
{
	const char *branch_color = color(WT_STATUS_ONBRANCH, s);
	const char *branch_status_color = color(WT_STATUS_HEADER, s);
	struct wt_status_state state;

	memset(&state, 0, sizeof(state));
	wt_status_get_state(&state,
			    s->branch && !strcmp(s->branch, "HEAD"));

	if (s->branch) {
		const char *on_what = _("On branch ");
		const char *branch_name = s->branch;
		if (!strcmp(branch_name, "HEAD")) {
			branch_status_color = color(WT_STATUS_NOBRANCH, s);
			if (state.rebase_in_progress || state.rebase_interactive_in_progress) {
				if (state.rebase_interactive_in_progress)
					on_what = _("interactive rebase in progress; onto ");
				else
					on_what = _("rebase in progress; onto ");
				branch_name = state.onto;
			} else if (state.detached_from) {
				branch_name = state.detached_from;
				if (state.detached_at)
					on_what = _("HEAD detached at ");
				else
					on_what = _("HEAD detached from ");
			} else {
				branch_name = "";
				on_what = _("Not currently on any branch.");
			}
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
					 s->untracked_in_ms / 1000.0);
		}
	} else if (s->commitable)
		status_printf_ln(s, GIT_COLOR_NORMAL, _("Untracked files not listed%s"),
			s->hints
			? _(" (use -u option to show untracked files)") : "");

	if (s->verbose)
		wt_longstatus_print_verbose(s);
	if (!s->commitable) {
		if (s->amend)
			status_printf_ln(s, GIT_COLOR_NORMAL, _("No changes"));
		else if (s->nowarn)
			; /* nothing */
		else if (s->workdir_dirty) {
			if (s->hints)
				printf(_("no changes added to commit "
					 "(use \"git add\" and/or \"git commit -a\")\n"));
			else
				printf(_("no changes added to commit\n"));
		} else if (s->untracked.nr) {
			if (s->hints)
				printf(_("nothing added to commit but untracked files "
					 "present (use \"git add\" to track)\n"));
			else
				printf(_("nothing added to commit but untracked files present\n"));
		} else if (s->is_initial) {
			if (s->hints)
				printf(_("nothing to commit (create/copy files "
					 "and use \"git add\" to track)\n"));
			else
				printf(_("nothing to commit\n"));
		} else if (!s->show_untracked_files) {
			if (s->hints)
				printf(_("nothing to commit (use -u to show untracked files)\n"));
			else
				printf(_("nothing to commit\n"));
		} else
			printf(_("nothing to commit, working tree clean\n"));
	}
}