		status_printf_ln(s, c, _("  (use \"git add <file>...\" to update what will be committed)"));
	else
		status_printf_ln(s, c, _("  (use \"git add/rm <file>...\" to update what will be committed)"));
	status_printf_ln(s, c, _("  (use \"git checkout -- <file>...\" to discard changes in working directory)"));
	if (has_dirty_submodules)
		status_printf_ln(s, c, _("  (commit or discard the untracked or modified content in submodules)"));
	status_printf_ln(s, c, "%s", "");
}

static void wt_status_print_other_header(struct wt_status *s,
					 const char *what,
					 const char *how)
{
	const char *c = color(WT_STATUS_HEADER, s);
	status_printf_ln(s, c, "%s:", what);
	if (!s->hints)
		return;
	status_printf_ln(s, c, _("  (use \"git %s <file>...\" to include in what will be committed)"), how);
	status_printf_ln(s, c, "%s", "");
}

static void wt_status_print_trailer(struct wt_status *s)
{
	status_printf_ln(s, color(WT_STATUS_HEADER, s), "%s", "");
}

#define quote_path quote_path_relative

static const char *wt_status_unmerged_status_string(int stagemask)
{
