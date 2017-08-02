{
	struct archive_read *a = (struct archive_read *)_a;
	struct archive_read_filter_bidder *bidder;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_filter_gzip");

	if (__archive_read_get_bidder(a, &bidder) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	bidder->data = NULL;
	bidder->name = "gzip";
	bidder->bid = gzip_bidder_bid;
	bidder->init = gzip_bidder_init;
	bidder->options = NULL;
	bidder->free = NULL; /* No data, so no cleanup necessary. */
	/* Signal the extent of gzip support with the return value here. */
#if HAVE_ZLIB_H
	return (ARCHIVE_OK);
#else
	archive_set_error(_a, ARCHIVE_ERRNO_MISC,
	    "Using external gzip program");
	return (ARCHIVE_WARN);
#endif
}