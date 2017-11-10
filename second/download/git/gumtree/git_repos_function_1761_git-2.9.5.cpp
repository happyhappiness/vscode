struct string_list_item *string_list_append(struct string_list *list,
					    const char *string)
{
	return string_list_append_nodup(
			list,
			list->strdup_strings ? xstrdup(string) : (char *)string);
}