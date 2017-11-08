void finish_writing_split_index(struct index_state *istate)
{
	struct split_index *si = init_split_index(istate);

	ewah_free(si->delete_bitmap);
	ewah_free(si->replace_bitmap);
	si->delete_bitmap = NULL;
	si->replace_bitmap = NULL;
	free(istate->cache);
	istate->cache = si->saved_cache;
	istate->cache_nr = si->saved_cache_nr;
}