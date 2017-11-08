void update_index_if_able(struct index_state *istate, struct lock_file *lockfile)
{
	if ((istate->cache_changed || has_racy_timestamp(istate)) &&
	    verify_index(istate) &&
	    write_locked_index(istate, lockfile, COMMIT_LOCK))
		rollback_lock_file(lockfile);
}