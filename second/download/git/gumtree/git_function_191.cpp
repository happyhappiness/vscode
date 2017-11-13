static void wt_status_print_dirty_header(struct wt_status *s,
					 int has_deleted,
					 int has_dirty_submodules)
{
	const char *c = color(WT_STATUS_HEADER, s);

	status_printf_ln(s, c, _("Changes not staged for commit:"));
	if (!s->hints)
		return;
	if (!has_deleted)
		status_printf_ln(s, c, _("  (use \"git add <file>...\" to update what will be committed)"));
	else
		status_printf_ln(s, c, _("  (use \"git add/rm <file>...\" to update what will be committed)"));
	status_printf_ln(s, c, _("  (use \"git checkout -- <file>...\" to discard changes in working directory)"));
	if (has_dirty_submodules)
		status_printf_ln(s, c, _("  (commit or discard the untracked or modified content in submodules)"));
	status_printf_ln(s, c, "");
}