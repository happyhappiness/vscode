struct string_list_item *unsorted_string_list_lookup(struct string_list *list,
						     const char *string)
{
	int i;
	compare_strings_fn cmp = list->cmp ? list->cmp : strcmp;

	for (i = 0; i < list->nr; i++)
		if (!cmp(string, list->items[i].string))
			return list->items + i;
	return NULL;
}