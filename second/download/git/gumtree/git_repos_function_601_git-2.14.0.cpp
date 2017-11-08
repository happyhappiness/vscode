void ref_array_clear(struct ref_array *array)
{
	int i;

	for (i = 0; i < array->nr; i++)
		free_array_item(array->items[i]);
	FREE_AND_NULL(array->items);
	array->nr = array->alloc = 0;
}