int
archive_read_disk_set_atime_restored(struct archive *_a)
{
#ifndef HAVE_UTIMES
	static int warning_done = 0;
#endif
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_ANY, "archive_read_disk_restore_atime");
#ifdef HAVE_UTIMES
	a->restore_time = 1;
	if (a->tree != NULL)
		a->tree->flags |= needsRestoreTimes;
	return (ARCHIVE_OK);
#else
	if (warning_done)
		/* Warning was already emitted; suppress further warnings. */
		return (ARCHIVE_OK);

	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
	    "Cannot restore access time on this system");
	warning_done = 1;
	return (ARCHIVE_WARN);
#endif
}
