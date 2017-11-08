void string_list_remove_duplicates(struct string_list *list, int free_util)
{
	if (list->nr > 1) {
		int src, dst;
		compare_strings_fn cmp = list->cmp ? list->cmp : strcmp;
		for (src = dst = 1; src < list->nr; src++) {
			if (!cmp(list->items[dst - 1].string, list->items[src].string)) {
				if (list->strdup_strings)
					free(list->items[src].string);
				if (free_util)
					free(list->items[src].util);
			} else
				list->items[dst++] = list->items[src];
		}
		list->nr = dst;
	}
}