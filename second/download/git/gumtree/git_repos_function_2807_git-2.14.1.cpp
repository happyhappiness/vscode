static void free_complete_reflog(struct complete_reflogs *array)
{
	int i;

	if (!array)
		return;

	for (i = 0; i < array->nr; i++) {
		free(array->items[i].email);
		free(array->items[i].message);
	}
	free(array->items);
	free(array->ref);
	free(array);
}