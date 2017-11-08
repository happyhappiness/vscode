static time_t rerere_created_at(const char *name)
{
	struct stat st;
	return stat(rerere_path(name, "preimage"), &st) ? (time_t) 0 : st.st_mtime;
}