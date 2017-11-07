void update_index_if_able(struct index_state *istate, struct lock_file *lockfile)
{
	if ((istate->cache_changed || has_racy_timestamp(istate)) &&
	    verify_index(istate) && !write_index(istate, lockfile->fd))
		commit_locked_index(lockfile);
	else
		rollback_lock_file(lockfile);
}