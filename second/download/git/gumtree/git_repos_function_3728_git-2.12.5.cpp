static inline FILE *get_lock_file_fp(struct lock_file *lk)
{
	return get_tempfile_fp(&lk->tempfile);
}