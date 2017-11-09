int urlmatch_config_entry(const char *var, const char *value, void *cb)
{
	struct string_list_item *item;
	struct urlmatch_config *collect = cb;
	struct urlmatch_item matched = {0};
	struct url_info *url = &collect->url;
	const char *key, *dot;
	struct strbuf synthkey = STRBUF_INIT;
	int retval;

	if (!skip_prefix(var, collect->section, &key) || *(key++) != '.') {
		if (collect->cascade_fn)
			return collect->cascade_fn(var, value, cb);
		return 0; /* not interested */
	}
	dot = strrchr(key, '.');
	if (dot) {
		char *config_url, *norm_url;
		struct url_info norm_info;

		config_url = xmemdupz(key, dot - key);
		norm_url = url_normalize_1(config_url, &norm_info, 1);
		free(config_url);
		if (!norm_url)
			return 0;
		retval = match_urls(url, &norm_info, &matched);
		free(norm_url);
		if (!retval)
			return 0;
		key = dot + 1;
	}

	if (collect->key && strcmp(key, collect->key))
		return 0;

	item = string_list_insert(&collect->vars, key);
	if (!item->util) {
		item->util = xcalloc(1, sizeof(matched));
	} else {
		if (cmp_matches(&matched, item->util) < 0)
			 /*
			  * Our match is worse than the old one,
			  * we cannot use it.
			  */
			return 0;
		/* Otherwise, replace it with this one. */
	}

	memcpy(item->util, &matched, sizeof(matched));
	strbuf_addstr(&synthkey, collect->section);
	strbuf_addch(&synthkey, '.');
	strbuf_addstr(&synthkey, key);
	retval = collect->collect_fn(synthkey.buf, value, collect->cb);

	strbuf_release(&synthkey);
	return retval;
}