struct worktree **get_worktrees(void)
{
	struct worktree **list = NULL;
	struct strbuf path = STRBUF_INIT;
	DIR *dir;
	struct dirent *d;
	int counter = 0, alloc = 2;

	list = xmalloc(alloc * sizeof(struct worktree *));

	if ((list[counter] = get_main_worktree()))
		counter++;

	strbuf_addf(&path, "%s/worktrees", get_git_common_dir());
	dir = opendir(path.buf);
	strbuf_release(&path);
	if (dir) {
		while ((d = readdir(dir)) != NULL) {
			struct worktree *linked = NULL;
			if (is_dot_or_dotdot(d->d_name))
				continue;

			if ((linked = get_linked_worktree(d->d_name))) {
				ALLOC_GROW(list, counter + 1, alloc);
				list[counter++] = linked;
			}
		}
		closedir(dir);
	}
	ALLOC_GROW(list, counter + 1, alloc);
	list[counter] = NULL;

	mark_current_worktree(list);
	return list;
}