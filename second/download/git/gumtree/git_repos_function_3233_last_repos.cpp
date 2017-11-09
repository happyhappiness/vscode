static int clear_ce_flags_dir(struct cache_entry **cache, int nr,
			      struct strbuf *prefix,
			      char *basename,
			      int select_mask, int clear_mask,
			      struct exclude_list *el, int defval)
{
	struct cache_entry **cache_end;
	int dtype = DT_DIR;
	int ret = is_excluded_from_list(prefix->buf, prefix->len,
					basename, &dtype, el, &the_index);
	int rc;

	strbuf_addch(prefix, '/');

	/* If undecided, use matching result of parent dir in defval */
	if (ret < 0)
		ret = defval;

	for (cache_end = cache; cache_end != cache + nr; cache_end++) {
		struct cache_entry *ce = *cache_end;
		if (strncmp(ce->name, prefix->buf, prefix->len))
			break;
	}

	/*
	 * TODO: check el, if there are no patterns that may conflict
	 * with ret (iow, we know in advance the incl/excl
	 * decision for the entire directory), clear flag here without
	 * calling clear_ce_flags_1(). That function will call
	 * the expensive is_excluded_from_list() on every entry.
	 */
	rc = clear_ce_flags_1(cache, cache_end - cache,
			      prefix,
			      select_mask, clear_mask,
			      el, ret);
	strbuf_setlen(prefix, prefix->len - 1);
	return rc;
}