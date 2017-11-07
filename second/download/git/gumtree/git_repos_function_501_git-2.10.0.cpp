void ref_array_clear(struct ref_array *array)
{
	int i;

	for (i = 0; i < array->nr; i++)
		free_array_item(array->items[i]);
	free(array->items);
	array->items = NULL;
	array->nr = array->alloc = 0;
}