static void prune_worktrees(void)
{
	struct strbuf reason = STRBUF_INIT;
	struct strbuf path = STRBUF_INIT;
	DIR *dir = opendir(git_path("worktrees"));
	struct dirent *d;
	int ret;
	if (!dir)
		return;
	while ((d = readdir(dir)) != NULL) {
		if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, ".."))
			continue;
		strbuf_reset(&reason);
		if (!prune_worktree(d->d_name, &reason))
			continue;
		if (show_only || verbose)
			printf("%s\n", reason.buf);
		if (show_only)
			continue;
		strbuf_reset(&path);
		strbuf_addstr(&path, git_path("worktrees/%s", d->d_name));
		ret = remove_dir_recursively(&path, 0);
		if (ret < 0 && errno == ENOTDIR)
			ret = unlink(path.buf);
		if (ret)
			error(_("failed to remove: %s"), strerror(errno));
	}
	closedir(dir);
	if (!show_only)
		rmdir(git_path("worktrees"));
	strbuf_release(&reason);
	strbuf_release(&path);
}