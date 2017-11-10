int string_list_find_insert_index(const struct string_list *list, const char *string,
				  int negative_existing_index)
{
	int exact_match;
	int index = get_entry_index(list, string, &exact_match);
	if (exact_match)
		index = -1 - (negative_existing_index ? index : 0);
	return index;
}