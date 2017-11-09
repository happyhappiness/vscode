static void display_plain(const struct string_list *list,
			  const char *indent, const char *nl)
{
	int i;

	for (i = 0; i < list->nr; i++)
		printf("%s%s%s", indent, list->items[i].string, nl);
}