struct string_list_item *string_list_insert_at_index(struct string_list *list,
						     int insert_at, const char *string)
{
	int index = add_entry(insert_at, list, string);

	if (index < 0)
		index = -1 - index;

	return list->items + index;
}