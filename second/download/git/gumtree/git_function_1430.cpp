static void wt_longstatus_print_stash_summary(struct wt_status *s)
{
	int stash_count = 0;

	for_each_reflog_ent("refs/stash", stash_count_refs, &stash_count);
	if (stash_count > 0)
		status_printf_ln(s, GIT_COLOR_NORMAL,
				 Q_("Your stash currently has %d entry",
				    "Your stash currently has %d entries", stash_count),
				 stash_count);
}