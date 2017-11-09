void resolve_undo_clear_index(struct index_state *istate)
{
	struct string_list *resolve_undo = istate->resolve_undo;
	if (!resolve_undo)
		return;
	string_list_clear(resolve_undo, 1);
	free(resolve_undo);
	istate->resolve_undo = NULL;
	istate->cache_changed |= RESOLVE_UNDO_CHANGED;
}