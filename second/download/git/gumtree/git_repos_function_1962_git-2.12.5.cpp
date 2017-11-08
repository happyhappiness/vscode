struct string_list_item *string_list_insert(struct string_list *list, const char *string)
{
	int index = add_entry(-1, list, string);

	if (index < 0)
		index = -1 - index;

	return list->items + index;
}