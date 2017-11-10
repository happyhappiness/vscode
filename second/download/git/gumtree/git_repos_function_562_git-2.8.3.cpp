static void configset_iter(struct config_set *cs, config_fn_t fn, void *data)
{
	int i, value_index;
	struct string_list *values;
	struct config_set_element *entry;
	struct configset_list *list = &cs->list;
	struct key_value_info *kv_info;

	for (i = 0; i < list->nr; i++) {
		entry = list->items[i].e;
		value_index = list->items[i].value_index;
		values = &entry->value_list;
		if (fn(entry->key, values->items[value_index].string, data) < 0) {
			kv_info = values->items[value_index].util;
			git_die_config_linenr(entry->key, kv_info->filename, kv_info->linenr);
		}
	}
}