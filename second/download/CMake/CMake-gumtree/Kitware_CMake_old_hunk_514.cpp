		    &data->child_stdout);

	if (child == -1) {

		archive_set_error(f->archive, EINVAL,

		    "Can't initialise filter");

		return (ARCHIVE_FATAL);

	}

#if defined(_WIN32) && !defined(__CYGWIN__)

