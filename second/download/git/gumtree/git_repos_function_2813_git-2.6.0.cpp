static int close_ref(struct ref_lock *lock)
{
	if (close_lock_file(lock->lk))
		return -1;
	return 0;
}