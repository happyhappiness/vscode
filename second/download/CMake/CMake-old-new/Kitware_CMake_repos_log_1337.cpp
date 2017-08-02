archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
	    "Failed to connect 'CL' pointer to 'RE' rr_moved pointer of "
	    "Rockridge extensions: current position = %jd, CL offset = %jd",
	    (intmax_t)iso9660->current_position, (intmax_t)file->cl_offset)