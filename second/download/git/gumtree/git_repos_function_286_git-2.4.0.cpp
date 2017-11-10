static struct cache_entry *create_alias_ce(struct index_state *istate,
					   struct cache_entry *ce,
					   struct cache_entry *alias)
{
	int len;
	struct cache_entry *new;

	if (alias->ce_flags & CE_ADDED)
		die("Will not add file alias '%s' ('%s' already exists in index)", ce->name, alias->name);

	/* Ok, create the new entry using the name of the existing alias */
	len = ce_namelen(alias);
	new = xcalloc(1, cache_entry_size(len));
	memcpy(new->name, alias->name, len);
	copy_cache_entry(new, ce);
	save_or_free_index_entry(istate, ce);
	return new;
}