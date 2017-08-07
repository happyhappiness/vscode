archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "%s decompression failed(%d)",
			    (xar->entry_encoding == XZ)?"xz":"lzma",
			    r);