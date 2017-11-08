static void status_init_config(struct wt_status *s, config_fn_t fn)
{
	wt_status_prepare(s);
	gitmodules_config();
	git_config(fn, s);
	determine_whence(s);
	s->hints = advice_status_hints; /* must come after git_config() */
}