static time_t rerere_last_used_at(const char *name)
{
	struct stat st;
	return stat(rerere_path(name, "postimage"), &st) ? (time_t) 0 : st.st_mtime;
}