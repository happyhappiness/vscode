static void wt_status_print_cached_header(struct wt_status *s)
{
	const char *c = color(WT_STATUS_HEADER, s);

	status_printf_ln(s, c, _("Changes to be committed:"));
	if (!s->hints)
		return;
	if (s->whence != FROM_COMMIT)
		; /* NEEDSWORK: use "git reset --unresolve"??? */
	else if (!s->is_initial)
		status_printf_ln(s, c, _("  (use \"git reset %s <file>...\" to unstage)"), s->reference);
	else
		status_printf_ln(s, c, _("  (use \"git rm --cached <file>...\" to unstage)"));
	status_printf_ln(s, c, "");
}