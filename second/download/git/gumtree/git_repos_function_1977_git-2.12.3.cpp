struct string_list_item *unsorted_string_list_lookup(struct string_list *list,
						     const char *string)
{
	struct string_list_item *item;
	compare_strings_fn cmp = list->cmp ? list->cmp : strcmp;

	for_each_string_list_item(item, list)
		if (!cmp(string, item->string))
			return item;
	return NULL;
}