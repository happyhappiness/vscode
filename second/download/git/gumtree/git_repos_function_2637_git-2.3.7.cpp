void unlock_ref(struct ref_lock *lock)
{
	/* Do not free lock->lk -- atexit() still looks at them */
	if (lock->lk)
		rollback_lock_file(lock->lk);
	free(lock->ref_name);
	free(lock->orig_ref_name);
	free(lock);
}