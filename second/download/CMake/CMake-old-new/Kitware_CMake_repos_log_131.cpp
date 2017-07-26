archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid uncompressed size (%d < %d)",
		    uavail, cfdata->uncompressed_size);