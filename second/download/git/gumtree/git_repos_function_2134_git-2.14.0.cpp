int for_each_string_list(struct string_list *list,
			 string_list_each_func_t fn, void *cb_data)
{
	int i, ret = 0;
	for (i = 0; i < list->nr; i++)
		if ((ret = fn(&list->items[i], cb_data)))
			break;
	return ret;
}