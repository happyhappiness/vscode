void rollback_lock_file(struct lock_file *lk)
{
	if (!lk->active)
		return;

	if (!close_lock_file(lk)) {
		unlink_or_warn(lk->filename.buf);
		lk->active = 0;
		strbuf_reset(&lk->filename);
	}
}