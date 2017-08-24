		size = extattr_get_file(accpath, namespace, name, value, size);

	if (size == -1) {
		archive_set_error(&a->archive, errno,
		    "Couldn't read extended attribute");
		return (ARCHIVE_WARN);
