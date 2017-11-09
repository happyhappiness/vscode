void clear_pathspec(struct pathspec *pathspec)
{
	int i, j;

	for (i = 0; i < pathspec->nr; i++) {
		free(pathspec->items[i].match);
		free(pathspec->items[i].original);

		for (j = 0; j < pathspec->items[i].attr_match_nr; j++)
			free(pathspec->items[i].attr_match[j].value);
		free(pathspec->items[i].attr_match);

		if (pathspec->items[i].attr_check)
			attr_check_free(pathspec->items[i].attr_check);
	}

	FREE_AND_NULL(pathspec->items);
	pathspec->nr = 0;
}