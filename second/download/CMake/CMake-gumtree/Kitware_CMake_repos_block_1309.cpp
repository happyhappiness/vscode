{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Ignoring out-of-order directory (%s) %jd > %jd",
		    parent->name.s,
		    (intmax_t)iso9660->current_position,
		    (intmax_t)parent->offset);
		return (ARCHIVE_WARN);
	}