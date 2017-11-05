static void update_linked_gitdir(const char *gitfile, const char *gitdir)
{
	struct strbuf path = STRBUF_INIT;
	struct stat st;

	strbuf_addf(&path, "%s/gitdir", gitdir);
	if (stat(path.buf, &st) || st.st_mtime + 24 * 3600 < time(NULL))
		write_file(path.buf, "%s", gitfile);
	strbuf_release(&path);
}