	else if (config_source && config_source->blob)
		return git_config_from_blob_ref(fn, config_source->blob, data);

	return do_git_config_sequence(opts, fn, data);
}

static void configset_iter(struct config_set *cs, config_fn_t fn, void *data)
{
	int i, value_index;
	struct string_list *values;
	struct config_set_element *entry;
	struct configset_list *list = &cs->list;
