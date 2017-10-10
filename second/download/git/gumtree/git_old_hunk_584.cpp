	} else if (s->commitable)
		status_printf_ln(s, GIT_COLOR_NORMAL, _("Untracked files not listed%s"),
			s->hints
			? _(" (use -u option to show untracked files)") : "");

	if (s->verbose)
		wt_status_print_verbose(s);
	if (!s->commitable) {
		if (s->amend)
			status_printf_ln(s, GIT_COLOR_NORMAL, _("No changes"));
		else if (s->nowarn)
			; /* nothing */
		else if (s->workdir_dirty) {
