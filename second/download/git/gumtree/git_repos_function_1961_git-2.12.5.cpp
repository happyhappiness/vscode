static int add_entry(int insert_at, struct string_list *list, const char *string)
{
	int exact_match = 0;
	int index = insert_at != -1 ? insert_at : get_entry_index(list, string, &exact_match);

	if (exact_match)
		return -1 - index;

	if (list->nr + 1 >= list->alloc) {
		list->alloc += 32;
		REALLOC_ARRAY(list->items, list->alloc);
	}
	if (index < list->nr)
		memmove(list->items + index + 1, list->items + index,
				(list->nr - index)
				* sizeof(struct string_list_item));
	list->items[index].string = list->strdup_strings ?
		xstrdup(string) : (char *)string;
	list->items[index].util = NULL;
	list->nr++;

	return index;
}