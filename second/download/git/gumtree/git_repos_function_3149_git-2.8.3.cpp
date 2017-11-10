static int dir_in_way(const char *path, int check_working_copy)
{
	int pos;
	struct strbuf dirpath = STRBUF_INIT;
	struct stat st;

	strbuf_addstr(&dirpath, path);
	strbuf_addch(&dirpath, '/');

	pos = cache_name_pos(dirpath.buf, dirpath.len);

	if (pos < 0)
		pos = -1 - pos;
	if (pos < active_nr &&
	    !strncmp(dirpath.buf, active_cache[pos]->name, dirpath.len)) {
		strbuf_release(&dirpath);
		return 1;
	}

	strbuf_release(&dirpath);
	return check_working_copy && !lstat(path, &st) && S_ISDIR(st.st_mode);
}