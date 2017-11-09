void git_configset_clear(struct config_set *cs)
{
	struct config_set_element *entry;
	struct hashmap_iter iter;
	if (!cs->hash_initialized)
		return;

	hashmap_iter_init(&cs->config_hash, &iter);
	while ((entry = hashmap_iter_next(&iter))) {
		free(entry->key);
		string_list_clear(&entry->value_list, 1);
	}
	hashmap_free(&cs->config_hash, 1);
	cs->hash_initialized = 0;
	free(cs->list.items);
	cs->list.nr = 0;
	cs->list.alloc = 0;
	cs->list.items = NULL;
}