int unmerge_index_entry_at(struct index_state *istate, int pos)
{
	const struct cache_entry *ce;
	struct string_list_item *item;
	struct resolve_undo_info *ru;
	int i, err = 0, matched;
	char *name;

	if (!istate->resolve_undo)
		return pos;

	ce = istate->cache[pos];
	if (ce_stage(ce)) {
		/* already unmerged */
		while ((pos < istate->cache_nr) &&
		       ! strcmp(istate->cache[pos]->name, ce->name))
			pos++;
		return pos - 1; /* return the last entry processed */
	}
	item = string_list_lookup(istate->resolve_undo, ce->name);
	if (!item)
		return pos;
	ru = item->util;
	if (!ru)
		return pos;
	matched = ce->ce_flags & CE_MATCHED;
	name = xstrdup(ce->name);
	remove_index_entry_at(istate, pos);
	for (i = 0; i < 3; i++) {
		struct cache_entry *nce;
		if (!ru->mode[i])
			continue;
		nce = make_cache_entry(ru->mode[i], ru->sha1[i],
				       name, i + 1, 0);
		if (matched)
			nce->ce_flags |= CE_MATCHED;
		if (add_index_entry(istate, nce, ADD_CACHE_OK_TO_ADD)) {
			err = 1;
			error("cannot unmerge '%s'", name);
		}
	}
	free(name);
	if (err)
		return pos;
	free(ru);
	item->util = NULL;
	return unmerge_index_entry_at(istate, pos);
}