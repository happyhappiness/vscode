void clear_pathspec(struct pathspec *pathspec)
{
	free(pathspec->items);
	pathspec->items = NULL;
}