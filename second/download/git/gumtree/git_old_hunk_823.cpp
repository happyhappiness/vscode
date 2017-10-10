}

/*
 * Follow the chain of deltas from this entry onward, throwing away any links
 * that cause us to hit a cycle (as determined by the DFS state flags in
 * the entries).
 */
static void break_delta_chains(struct object_entry *entry)
{
	/* If it's not a delta, it can't be part of a cycle. */
	if (!entry->delta) {
		entry->dfs_state = DFS_DONE;
		return;
	}

	switch (entry->dfs_state) {
	case DFS_NONE:
		/*
		 * This is the first time we've seen the object. We mark it as
		 * part of the active potential cycle and recurse.
		 */
		entry->dfs_state = DFS_ACTIVE;
		break_delta_chains(entry->delta);
		entry->dfs_state = DFS_DONE;
		break;

	case DFS_DONE:
		/* object already examined, and not part of a cycle */
		break;

	case DFS_ACTIVE:
		/*
		 * We found a cycle that needs broken. It would be correct to
		 * break any link in the chain, but it's convenient to
		 * break this one.
		 */
		drop_reused_delta(entry);
		entry->dfs_state = DFS_DONE;
		break;
	}
}

static void get_object_details(void)
{
	uint32_t i;
