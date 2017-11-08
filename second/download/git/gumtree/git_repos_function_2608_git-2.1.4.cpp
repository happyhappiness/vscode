int setup_rerere(struct string_list *merge_rr, int flags)
{
	int fd;

	git_config(git_rerere_config, NULL);
	if (!is_rerere_enabled())
		return -1;

	if (flags & (RERERE_AUTOUPDATE|RERERE_NOAUTOUPDATE))
		rerere_autoupdate = !!(flags & RERERE_AUTOUPDATE);
	merge_rr_path = git_pathdup("MERGE_RR");
	fd = hold_lock_file_for_update(&write_lock, merge_rr_path,
				       LOCK_DIE_ON_ERROR);
	read_rr(merge_rr);
	return fd;
}