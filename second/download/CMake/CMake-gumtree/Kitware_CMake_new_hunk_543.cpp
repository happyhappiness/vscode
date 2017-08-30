

	if (status != 0) {

		archive_set_error(f->archive, EIO,

		    "Error closing program: %s", data->program_name);

		ret = ARCHIVE_FATAL;

	}

	r1 = __archive_write_close_filter(f->next_filter);
