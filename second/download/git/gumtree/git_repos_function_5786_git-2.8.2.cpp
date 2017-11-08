static int delete_ref_loose(struct ref_lock *lock, int flag, struct strbuf *err)
{
	assert(err);

	if (!(flag & REF_ISPACKED) || flag & REF_ISSYMREF) {
		/*
		 * loose.  The loose file name is the same as the
		 * lockfile name, minus ".lock":
		 */
		char *loose_filename = get_locked_file_path(lock->lk);
		int res = unlink_or_msg(loose_filename, err);
		free(loose_filename);
		if (res)
			return 1;
	}
	return 0;
}