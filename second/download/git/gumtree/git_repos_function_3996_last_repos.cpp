static inline FILE *fdopen_lock_file(struct lock_file *lk, const char *mode)
{
	return fdopen_tempfile(&lk->tempfile, mode);
}