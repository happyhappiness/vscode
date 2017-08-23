{
		archive_set_error(f->archive, EIO,
		    "Error closing program: %s", data->program_name);
		ret = ARCHIVE_FATAL;
	}