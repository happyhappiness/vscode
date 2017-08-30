			archive_set_error(&a->archive, ENOMEM, "Out of memory");

			return (ARCHIVE_FATAL);

		}

		p = calloc(new_size, sizeof(p[0]));

		if (p == NULL) {

			archive_set_error(&a->archive, ENOMEM, "Out of memory");

			return (ARCHIVE_FATAL);

