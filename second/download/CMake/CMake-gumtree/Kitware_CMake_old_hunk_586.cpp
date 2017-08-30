		return (r);

	if ((size_t)r < size) {

		archive_set_error(&a->archive, 0,

		    "Write request too large");

		return (ARCHIVE_WARN);

	}

	return (ARCHIVE_OK);

}



static ssize_t

