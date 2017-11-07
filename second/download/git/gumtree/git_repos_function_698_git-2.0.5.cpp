static void wt_status_print_other_header(struct wt_status *s,
					 const char *what,
					 const char *how)
{
	const char *c = color(WT_STATUS_HEADER, s);
	status_printf_ln(s, c, "%s:", what);
	if (!s->hints)
		return;
	status_printf_ln(s, c, _("  (use \"git %s <file>...\" to include in what will be committed)"), how);
	status_printf_ln(s, c, "");
}