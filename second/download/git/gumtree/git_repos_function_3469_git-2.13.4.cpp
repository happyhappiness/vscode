static time_t rerere_created_at(struct rerere_id *id)
{
	struct stat st;

	return stat(rerere_path(id, "preimage"), &st) ? (time_t) 0 : st.st_mtime;
}