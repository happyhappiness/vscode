static void strip_submodule_slash_expensive(struct pathspec_item *item)
{
	int i;

	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];
		int ce_len = ce_namelen(ce);

		if (!S_ISGITLINK(ce->ce_mode))
			continue;

		if (item->len <= ce_len || item->match[ce_len] != '/' ||
		    memcmp(ce->name, item->match, ce_len))
			continue;

		if (item->len == ce_len + 1) {
			/* strip trailing slash */
			item->len--;
			item->match[item->len] = '\0';
		} else {
			die(_("Pathspec '%s' is in submodule '%.*s'"),
			    item->original, ce_len, ce->name);
		}
	}
}