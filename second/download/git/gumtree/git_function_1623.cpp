int commit_lock_file(struct lock_file *lk)
{
	static struct strbuf result_file = STRBUF_INIT;
	int err;

	if (!lk->active)
		die("BUG: attempt to commit unlocked object");

	if (lk->filename.len <= LOCK_SUFFIX_LEN ||
	    strcmp(lk->filename.buf + lk->filename.len - LOCK_SUFFIX_LEN, LOCK_SUFFIX))
		die("BUG: lockfile filename corrupt");

	/* remove ".lock": */
	strbuf_add(&result_file, lk->filename.buf,
		   lk->filename.len - LOCK_SUFFIX_LEN);
	err = commit_lock_file_to(lk, result_file.buf);
	strbuf_reset(&result_file);
	return err;
}