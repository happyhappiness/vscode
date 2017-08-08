{
		archive_set_error(&(a->archive),
		    ARCHIVE_ERRNO_MISC,
		    "The %s is encoded with many filters, "
		    "but currently not supported", cname);
		return (ARCHIVE_FATAL);
	}