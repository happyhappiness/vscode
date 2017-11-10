const char *find_hook(const char *name)
{
	static struct strbuf path = STRBUF_INIT;

	strbuf_reset(&path);
	if (git_hooks_path)
		strbuf_addf(&path, "%s/%s", git_hooks_path, name);
	else
		strbuf_git_path(&path, "hooks/%s", name);
	if (access(path.buf, X_OK) < 0)
		return NULL;
	return path.buf;
}