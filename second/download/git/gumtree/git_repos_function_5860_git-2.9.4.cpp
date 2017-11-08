static int commit_ref(struct ref_lock *lock)
{
	if (commit_lock_file(lock->lk))
		return -1;
	return 0;
}