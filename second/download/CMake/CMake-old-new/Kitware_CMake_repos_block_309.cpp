{
		archive_set_error(&a->archive, errno,
		    "Cannot restore xattr: %s at %u pos %u bytes",
		    XATTR_RESOURCEFORK_NAME,
		    (unsigned)position,
		    (unsigned)bytes);
		return (ARCHIVE_WARN);
	}