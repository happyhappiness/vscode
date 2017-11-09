struct worktree *find_worktree(struct worktree **list,
			       const char *prefix,
			       const char *arg)
{
	struct worktree *wt;
	char *path;
	char *to_free = NULL;

	if ((wt = find_worktree_by_suffix(list, arg)))
		return wt;

	if (prefix)
		arg = to_free = prefix_filename(prefix, arg);
	path = real_pathdup(arg, 1);
	for (; *list; list++)
		if (!fspathcmp(path, real_path((*list)->path)))
			break;
	free(path);
	free(to_free);
	return *list;
}