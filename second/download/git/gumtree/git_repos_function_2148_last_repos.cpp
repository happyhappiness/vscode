void string_list_clear_func(struct string_list *list, string_list_clear_func_t clearfunc)
{
	if (list->items) {
		int i;
		if (clearfunc) {
			for (i = 0; i < list->nr; i++)
				clearfunc(list->items[i].util, list->items[i].string);
		}
		if (list->strdup_strings) {
			for (i = 0; i < list->nr; i++)
				free(list->items[i].string);
		}
		free(list->items);
	}
	list->items = NULL;
	list->nr = list->alloc = 0;
}