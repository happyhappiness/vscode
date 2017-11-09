void clear_exclude_list(struct exclude_list *el)
{
	int i;

	for (i = 0; i < el->nr; i++)
		free(el->excludes[i]);
	free(el->excludes);
	free(el->filebuf);

	memset(el, 0, sizeof(*el));
}