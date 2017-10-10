
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

static int config_set_element_cmp(const struct config_set_element *e1,
