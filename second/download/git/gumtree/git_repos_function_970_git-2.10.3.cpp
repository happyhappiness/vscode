static void wt_shortstatus_print_tracking(struct wt_status *s)
{
	struct branch *branch;
	const char *header_color = color(WT_STATUS_HEADER, s);
	const char *branch_color_local = color(WT_STATUS_LOCAL_BRANCH, s);
	const char *branch_color_remote = color(WT_STATUS_REMOTE_BRANCH, s);

	const char *base;
	const char *branch_name;
	int num_ours, num_theirs;
	int upstream_is_gone = 0;

	color_fprintf(s->fp, color(WT_STATUS_HEADER, s), "## ");

	if (!s->branch)
		return;
	branch_name = s->branch;

	if (s->is_initial)
		color_fprintf(s->fp, header_color, _("Initial commit on "));

	if (!strcmp(s->branch, "HEAD")) {
		color_fprintf(s->fp, color(WT_STATUS_NOBRANCH, s), "%s",
			      _("HEAD (no branch)"));
		goto conclude;
	}

	skip_prefix(branch_name, "refs/heads/", &branch_name);

	branch = branch_get(branch_name);

	color_fprintf(s->fp, branch_color_local, "%s", branch_name);

	if (stat_tracking_info(branch, &num_ours, &num_theirs, &base) < 0) {
		if (!base)
			goto conclude;

		upstream_is_gone = 1;
	}

	base = shorten_unambiguous_ref(base, 0);
	color_fprintf(s->fp, header_color, "...");
	color_fprintf(s->fp, branch_color_remote, "%s", base);
	free((char *)base);

	if (!upstream_is_gone && !num_ours && !num_theirs)
		goto conclude;

#define LABEL(string) (s->no_gettext ? (string) : _(string))

	color_fprintf(s->fp, header_color, " [");
	if (upstream_is_gone) {
		color_fprintf(s->fp, header_color, LABEL(N_("gone")));
	} else if (!num_ours) {
		color_fprintf(s->fp, header_color, LABEL(N_("behind ")));
		color_fprintf(s->fp, branch_color_remote, "%d", num_theirs);
	} else if (!num_theirs) {
		color_fprintf(s->fp, header_color, LABEL(N_("ahead ")));
		color_fprintf(s->fp, branch_color_local, "%d", num_ours);
	} else {
		color_fprintf(s->fp, header_color, LABEL(N_("ahead ")));
		color_fprintf(s->fp, branch_color_local, "%d", num_ours);
		color_fprintf(s->fp, header_color, ", %s", LABEL(N_("behind ")));
		color_fprintf(s->fp, branch_color_remote, "%d", num_theirs);
	}

	color_fprintf(s->fp, header_color, "]");
 conclude:
	fputc(s->null_termination ? '\0' : '\n', s->fp);
}