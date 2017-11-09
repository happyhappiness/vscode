static void mark_all_ce_unused(struct index_state *index)
{
	int i;
	for (i = 0; i < index->cache_nr; i++)
		index->cache[i]->ce_flags &= ~(CE_UNPACKED | CE_ADDED | CE_NEW_SKIP_WORKTREE);
}