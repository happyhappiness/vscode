struct string_list_item *string_list_insert(struct string_list *list, const char *string)
{
	return string_list_insert_at_index(list, -1, string);
}