void string_list_init(struct string_list *list, int strdup_strings)
{
	memset(list, 0, sizeof(*list));
	list->strdup_strings = strdup_strings;
}