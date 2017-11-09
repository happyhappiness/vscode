static void configset_iter(struct config_set *cs, config_fn_t fn, void *data)
{
	int i, value_index;
	struct string_list *values;
	struct config_set_element *entry;
	struct configset_list *list = &cs->list;

	for (i = 0; i < list->nr; i++) {
		entry = list->items[i].e;
		value_index = list->items[i].value_index;
		values = &entry->value_list;

		current_config_kvi = values->items[value_index].util;

		if (fn(entry->key, values->items[value_index].string, data) < 0)
			git_die_config_linenr(entry->key,
					      current_config_kvi->filename,
					      current_config_kvi->linenr);

		current_config_kvi = NULL;
	}
}