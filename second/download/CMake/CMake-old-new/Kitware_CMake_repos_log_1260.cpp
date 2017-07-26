archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Internal Programing error: iso9660:wb_consume()"
		    " size=%jd, wbuff_remaining=%jd",
		    (intmax_t)size, (intmax_t)iso9660->wbuff_remaining);