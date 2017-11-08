char *find_shared_symref(const char *symref, const char *target)
{
	struct strbuf path = STRBUF_INIT;
	DIR *dir;
	struct dirent *d;
	char *existing;

	if ((existing = find_linked_symref(symref, target, NULL)))
		return existing;

	strbuf_addf(&path, "%s/worktrees", get_git_common_dir());
	dir = opendir(path.buf);
	strbuf_release(&path);
	if (!dir)
		return NULL;

	while ((d = readdir(dir)) != NULL) {
		if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, ".."))
			continue;
		existing = find_linked_symref(symref, target, d->d_name);
		if (existing)
			goto done;
	}
done:
	closedir(dir);

	return existing;
}