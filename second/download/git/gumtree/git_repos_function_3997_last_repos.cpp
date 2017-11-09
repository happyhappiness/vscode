static inline const char *get_lock_file_path(struct lock_file *lk)
{
	return get_tempfile_path(&lk->tempfile);
}