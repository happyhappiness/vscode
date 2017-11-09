static int prune_worktree(const char *id, struct strbuf *reason)
{
	struct stat st;
	char *path;
	int fd, len;

	if (!is_directory(git_path("worktrees/%s", id))) {
		strbuf_addf(reason, _("Removing worktrees/%s: not a valid directory"), id);
		return 1;
	}
	if (file_exists(git_path("worktrees/%s/locked", id)))
		return 0;
	if (stat(git_path("worktrees/%s/gitdir", id), &st)) {
		strbuf_addf(reason, _("Removing worktrees/%s: gitdir file does not exist"), id);
		return 1;
	}
	fd = open(git_path("worktrees/%s/gitdir", id), O_RDONLY);
	if (fd < 0) {
		strbuf_addf(reason, _("Removing worktrees/%s: unable to read gitdir file (%s)"),
			    id, strerror(errno));
		return 1;
	}
	len = st.st_size;
	path = xmallocz(len);
	read_in_full(fd, path, len);
	close(fd);
	while (len && (path[len - 1] == '\n' || path[len - 1] == '\r'))
		len--;
	if (!len) {
		strbuf_addf(reason, _("Removing worktrees/%s: invalid gitdir file"), id);
		free(path);
		return 1;
	}
	path[len] = '\0';
	if (!file_exists(path)) {
		struct stat st_link;
		free(path);
		/*
		 * the repo is moved manually and has not been
		 * accessed since?
		 */
		if (!stat(git_path("worktrees/%s/link", id), &st_link) &&
		    st_link.st_nlink > 1)
			return 0;
		if (st.st_mtime <= expire) {
			strbuf_addf(reason, _("Removing worktrees/%s: gitdir file points to non-existent location"), id);
			return 1;
		} else {
			return 0;
		}
	}
	free(path);
	return 0;
}