static inline int commit_lock_file_to(struct lock_file *lk, const char *path)
{
	return rename_tempfile(&lk->tempfile, path);
}