int urlmatch_config_entry(const char *var, const char *value, void *cb)
{
	struct string_list_item *item;
	struct urlmatch_config *collect = cb;
	struct urlmatch_item *matched;
	struct url_info *url = &collect->url;
	const char *key, *dot;
	struct strbuf synthkey = STRBUF_INIT;
	size_t matched_len = 0;
	int user_matched = 0;
	int retval;

	key = skip_prefix(var, collect->section);
	if (!key || *(key++) != '.') {
		if (collect->cascade_fn)
			return collect->cascade_fn(var, value, cb);
		return 0; /* not interested */
	}
	dot = strrchr(key, '.');
	if (dot) {
		char *config_url, *norm_url;
		struct url_info norm_info;

		config_url = xmemdupz(key, dot - key);
		norm_url = url_normalize(config_url, &norm_info);
		free(config_url);
		if (!norm_url)
			return 0;
		matched_len = match_urls(url, &norm_info, &user_matched);
		free(norm_url);
		if (!matched_len)
			return 0;
		key = dot + 1;
	}

	if (collect->key && strcmp(key, collect->key))
		return 0;

	item = string_list_insert(&collect->vars, key);
	if (!item->util) {
		matched = xcalloc(1, sizeof(*matched));
		item->util = matched;
	} else {
		matched = item->util;
		/*
		 * Is our match shorter?  Is our match the same
		 * length, and without user while the current
		 * candidate is with user?  Then we cannot use it.
		 */
		if (matched_len < matched->matched_len ||
		    ((matched_len == matched->matched_len) &&
		     (!user_matched && matched->user_matched)))
			return 0;
		/* Otherwise, replace it with this one. */
	}

	matched->matched_len = matched_len;
	matched->user_matched = user_matched;
	strbuf_addstr(&synthkey, collect->section);
	strbuf_addch(&synthkey, '.');
	strbuf_addstr(&synthkey, key);
	retval = collect->collect_fn(synthkey.buf, value, collect->cb);

	strbuf_release(&synthkey);
	return retval;
}