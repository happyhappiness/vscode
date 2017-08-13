archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Ignoring out-of-order file (%s) %jd < %jd",
			    iso9660->pathname.s,
			    (intmax_t)iso9660->entry_content->offset,
			    (intmax_t)iso9660->current_position);