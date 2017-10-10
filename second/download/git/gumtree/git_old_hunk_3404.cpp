
static void dump_marks(void)
{
	static struct lock_file mark_lock;
	FILE *f;

	if (!export_marks_file)
		return;

	if (hold_lock_file_for_update(&mark_lock, export_marks_file, 0) < 0) {
		failure |= error("Unable to write marks file %s: %s",
			export_marks_file, strerror(errno));
		return;
	}

	f = fdopen_lock_file(&mark_lock, "w");
	if (!f) {
		int saved_errno = errno;
