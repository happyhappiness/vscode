void add_untracked_cache(struct index_state *istate)
{
	if (!istate->untracked) {
		new_untracked_cache(istate);
	} else {
		if (!ident_in_untracked(istate->untracked)) {
			free_untracked_cache(istate->untracked);
			new_untracked_cache(istate);
		}
	}
}