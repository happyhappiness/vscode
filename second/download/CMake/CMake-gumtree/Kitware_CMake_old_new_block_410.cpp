{
		archive_set_error(f->archive, EIO,
		    "Filter exited with failure.");
		ret = ARCHIVE_FATAL;
	}