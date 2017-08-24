{
	struct archive_entry *ae;
	time_t ctime_sec, mtime_sec;
	long ctime_ns, mtime_ns;

	ae = archive_entry_new();
	if (ae == NULL)
		return (error_nomem(a));
	archive_entry_copy_stat(ae, st);
	ctime_sec = archive_entry_ctime(ae);
	ctime_ns = archive_entry_ctime_nsec(ae);
	mtime_sec = archive_entry_mtime(ae);
	mtime_ns = archive_entry_mtime_nsec(ae);
	archive_entry_free(ae);
	return set_timefilter(a, timetype, mtime_sec, mtime_ns,
			ctime_sec, ctime_ns);
}