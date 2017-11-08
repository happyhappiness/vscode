void clear_pathspec(struct pathspec *pathspec)
{
	int i;

	for (i = 0; i < pathspec->nr; i++) {
		free(pathspec->items[i].match);
		free(pathspec->items[i].original);
	}
	free(pathspec->items);
	pathspec->items = NULL;
	pathspec->nr = 0;
}