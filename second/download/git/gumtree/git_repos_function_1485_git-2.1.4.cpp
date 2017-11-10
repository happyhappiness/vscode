void filter_string_list(struct string_list *list, int free_util,
			string_list_each_func_t want, void *cb_data)
{
	int src, dst = 0;
	for (src = 0; src < list->nr; src++) {
		if (want(&list->items[src], cb_data)) {
			list->items[dst++] = list->items[src];
		} else {
			if (list->strdup_strings)
				free(list->items[src].string);
			if (free_util)
				free(list->items[src].util);
		}
	}
	list->nr = dst;
}