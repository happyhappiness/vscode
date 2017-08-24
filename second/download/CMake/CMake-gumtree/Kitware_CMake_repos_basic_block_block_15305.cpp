{
	time_t sec;
	long nsec;

	fileTimeToUtc(&st->ftLastWriteTime, &sec, &nsec);
	/* First, test the seconds and return if we have a definite answer. */
	/* Definitely older. */
	if (sec < archive_entry_mtime(entry))
		return (1);
	/* Definitely younger. */
	if (sec > archive_entry_mtime(entry))
		return (0);
	if (nsec < archive_entry_mtime_nsec(entry))
		return (1);
	/* Same age or newer, so not older. */
	return (0);
}