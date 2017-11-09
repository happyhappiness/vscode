void string_list_remove(struct string_list *list, const char *string,
			int free_util)
{
	int exact_match;
	int i = get_entry_index(list, string, &exact_match);

	if (exact_match) {
		if (list->strdup_strings)
			free(list->items[i].string);
		if (free_util)
			free(list->items[i].util);

		list->nr--;
		MOVE_ARRAY(list->items + i, list->items + i + 1, list->nr - i);
	}
}