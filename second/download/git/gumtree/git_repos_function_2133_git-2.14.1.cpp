struct string_list_item *string_list_lookup(struct string_list *list, const char *string)
{
	int exact_match, i = get_entry_index(list, string, &exact_match);
	if (!exact_match)
		return NULL;
	return list->items + i;
}