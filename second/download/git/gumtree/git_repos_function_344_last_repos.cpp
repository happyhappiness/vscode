int chmod_index_entry(struct index_state *istate, struct cache_entry *ce,
		      char flip)
{
	if (!S_ISREG(ce->ce_mode))
		return -1;
	switch (flip) {
	case '+':
		ce->ce_mode |= 0111;
		break;
	case '-':
		ce->ce_mode &= ~0111;
		break;
	default:
		return -2;
	}
	cache_tree_invalidate_path(istate, ce->name);
	ce->ce_flags |= CE_UPDATE_IN_BASE;
	istate->cache_changed |= CE_ENTRY_CHANGED;

	return 0;
}