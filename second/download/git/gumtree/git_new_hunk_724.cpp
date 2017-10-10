
/* This should return a meaningful errno on failure */
int hold_lock_file_for_update_timeout(struct lock_file *lk, const char *path,
				      int flags, long timeout_ms)
{
	int fd = lock_file_timeout(lk, path, flags, timeout_ms);
	if (fd < 0) {
		if (flags & LOCK_DIE_ON_ERROR)
			unable_to_lock_die(path, errno);
		if (flags & LOCK_REPORT_ON_ERROR) {
			struct strbuf buf = STRBUF_INIT;
			unable_to_lock_message(path, errno, &buf);
			error("%s", buf.buf);
			strbuf_release(&buf);
		}
	}
	return fd;
}

char *get_locked_file_path(struct lock_file *lk)
{
	struct strbuf ret = STRBUF_INIT;
