static int configset_add_value(struct config_set *cs, const char *key, const char *value)
{
	struct config_set_element *e;
	struct string_list_item *si;
	struct configset_list_item *l_item;
	struct key_value_info *kv_info = xmalloc(sizeof(*kv_info));

	e = configset_find_element(cs, key);
	/*
	 * Since the keys are being fed by git_config*() callback mechanism, they
	 * are already normalized. So simply add them without any further munging.
	 */
	if (!e) {
		e = xmalloc(sizeof(*e));
		hashmap_entry_init(e, strhash(key));
		e->key = xstrdup(key);
		string_list_init(&e->value_list, 1);
		hashmap_add(&cs->config_hash, e);
	}
	si = string_list_append_nodup(&e->value_list, xstrdup_or_null(value));

	ALLOC_GROW(cs->list.items, cs->list.nr + 1, cs->list.alloc);
	l_item = &cs->list.items[cs->list.nr++];
	l_item->e = e;
	l_item->value_index = e->value_list.nr - 1;

	if (!cf)
		die("BUG: configset_add_value has no source");
	if (cf->name) {
		kv_info->filename = strintern(cf->name);
		kv_info->linenr = cf->linenr;
		kv_info->origin_type = cf->origin_type;
	} else {
		/* for values read from `git_config_from_parameters()` */
		kv_info->filename = NULL;
		kv_info->linenr = -1;
		kv_info->origin_type = CONFIG_ORIGIN_CMDLINE;
	}
	kv_info->scope = current_parsing_scope;
	si->util = kv_info;

	return 0;
}