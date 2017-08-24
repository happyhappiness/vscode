{
	int r;
	if (length == 0)
		return(ARCHIVE_OK);
	if (f->write == NULL)
		/* If unset, a fatal error has already occurred, so this filter
		 * didn't open. We cannot write anything. */
		return(ARCHIVE_FATAL);
	r = (f->write)(f, buff, length);
	f->bytes_written += length;
	return (r);
}