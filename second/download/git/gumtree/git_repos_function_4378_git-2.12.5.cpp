static void die_inside_submodule_path(struct pathspec_item *item)
{
	int i;

	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];
		int ce_len = ce_namelen(ce);

		if (!S_ISGITLINK(ce->ce_mode))
			continue;

		if (item->len < ce_len ||
		    !(item->match[ce_len] == '/' || item->match[ce_len] == '\0') ||
		    memcmp(ce->name, item->match, ce_len))
			continue;

		die(_("Pathspec '%s' is in submodule '%.*s'"),
		    item->original, ce_len, ce->name);
	}
}