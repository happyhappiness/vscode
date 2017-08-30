		value = strdup(atts[1]);

		if (attr == NULL || name == NULL || value == NULL) {

			archive_set_error(&a->archive, ENOMEM, "Out of memory");

			return (ARCHIVE_FATAL);

		}

		attr->name = name;
