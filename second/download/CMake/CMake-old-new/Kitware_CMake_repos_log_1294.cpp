archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Ignoring out-of-order file @%jx (%s) %jd < %jd",
			    (intmax_t)file->number,
			    iso9660->pathname.s,
			    (intmax_t)file->offset,
			    (intmax_t)iso9660->current_position)