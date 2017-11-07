static time_t rerere_last_used_at(struct rerere_id *id)
{
	struct stat st;

	return stat(rerere_path(id, "postimage"), &st) ? (time_t) 0 : st.st_mtime;
}