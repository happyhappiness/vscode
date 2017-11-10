int string_list_has_string(const struct string_list *list, const char *string)
{
	int exact_match;
	get_entry_index(list, string, &exact_match);
	return exact_match;
}