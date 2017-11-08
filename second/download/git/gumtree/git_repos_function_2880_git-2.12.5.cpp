struct worktree *find_worktree(struct worktree **list,
			       const char *prefix,
			       const char *arg)
{
	struct worktree *wt;
	char *path;

	if ((wt = find_worktree_by_suffix(list, arg)))
		return wt;

	arg = prefix_filename(prefix, strlen(prefix), arg);
	path = real_pathdup(arg, 1);
	for (; *list; list++)
		if (!fspathcmp(path, real_path((*list)->path)))
			break;
	free(path);
	return *list;
}