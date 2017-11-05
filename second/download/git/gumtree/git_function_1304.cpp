char *get_locked_file_path(struct lock_file *lk)
{
	if (!lk->active)
		die("BUG: get_locked_file_path() called for unlocked object");
	if (lk->filename.len <= LOCK_SUFFIX_LEN)
		die("BUG: get_locked_file_path() called for malformed lock object");
	return xmemdupz(lk->filename.buf, lk->filename.len - LOCK_SUFFIX_LEN);
}