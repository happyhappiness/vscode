void unsorted_string_list_delete_item(struct string_list *list, int i, int free_util)
{
	if (list->strdup_strings)
		free(list->items[i].string);
	if (free_util)
		free(list->items[i].util);
	list->items[i] = list->items[list->nr-1];
	list->nr--;
}