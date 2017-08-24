(sc == NULL) {
		if (archive_string_append(as, _p, length) == NULL)
			return (-1);/* No memory */
		return (0);
	}