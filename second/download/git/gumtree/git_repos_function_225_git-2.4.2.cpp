static void remove_subtree(struct strbuf *path)
{
	DIR *dir = opendir(path->buf);
	struct dirent *de;
	int origlen = path->len;

	if (!dir)
		die_errno("cannot opendir '%s'", path->buf);
	while ((de = readdir(dir)) != NULL) {
		struct stat st;

		if (is_dot_or_dotdot(de->d_name))
			continue;

		strbuf_addch(path, '/');
		strbuf_addstr(path, de->d_name);
		if (lstat(path->buf, &st))
			die_errno("cannot lstat '%s'", path->buf);
		if (S_ISDIR(st.st_mode))
			remove_subtree(path);
		else if (unlink(path->buf))
			die_errno("cannot unlink '%s'", path->buf);
		strbuf_setlen(path, origlen);
	}
	closedir(dir);
	if (rmdir(path->buf))
		die_errno("cannot rmdir '%s'", path->buf);
}