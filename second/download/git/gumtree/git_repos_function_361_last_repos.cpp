int hold_locked_index(struct lock_file *lk, int lock_flags)
{
	return hold_lock_file_for_update(lk, get_index_file(), lock_flags);
}