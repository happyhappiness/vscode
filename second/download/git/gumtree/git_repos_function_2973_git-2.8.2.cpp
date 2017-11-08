static time_t rerere_last_used_at(const char *dir_name)
{
	struct stat st;
	struct rerere_id *id = dirname_to_id(dir_name);

	return stat(rerere_path(id, "postimage"), &st) ? (time_t) 0 : st.st_mtime;
}