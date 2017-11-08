static void check_linked_checkouts(struct branch_info *new)
{
	struct strbuf path = STRBUF_INIT;
	DIR *dir;
	struct dirent *d;

	strbuf_addf(&path, "%s/worktrees", get_git_common_dir());
	if ((dir = opendir(path.buf)) == NULL) {
		strbuf_release(&path);
		return;
	}

	/*
	 * $GIT_COMMON_DIR/HEAD is practically outside
	 * $GIT_DIR so resolve_ref_unsafe() won't work (it
	 * uses git_path). Parse the ref ourselves.
	 */
	check_linked_checkout(new, NULL);

	while ((d = readdir(dir)) != NULL) {
		if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, ".."))
			continue;
		check_linked_checkout(new, d->d_name);
	}
	strbuf_release(&path);
	closedir(dir);
}