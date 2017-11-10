static struct config_set_element *configset_find_element(struct config_set *cs, const char *key)
{
	struct config_set_element k;
	struct config_set_element *found_entry;
	char *normalized_key;
	/*
	 * `key` may come from the user, so normalize it before using it
	 * for querying entries from the hashmap.
	 */
	if (git_config_parse_key(key, &normalized_key, NULL))
		return NULL;

	hashmap_entry_init(&k, strhash(normalized_key));
	k.key = normalized_key;
	found_entry = hashmap_get(&cs->config_hash, &k, NULL);
	free(normalized_key);
	return found_entry;
}