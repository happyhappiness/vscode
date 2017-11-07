static int delete_ref_loose(struct ref_lock *lock, int flag)
{
	if (!(flag & REF_ISPACKED) || flag & REF_ISSYMREF) {
		/* loose */
		int err, i = strlen(lock->lk->filename) - 5; /* .lock */

		lock->lk->filename[i] = 0;
		err = unlink_or_warn(lock->lk->filename);
		lock->lk->filename[i] = '.';
		if (err && errno != ENOENT)
			return 1;
	}
	return 0;
}