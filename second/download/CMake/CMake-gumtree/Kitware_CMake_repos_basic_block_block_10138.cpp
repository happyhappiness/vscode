{
		struct archive_format_descriptor *format = &a->formats[i];

		if (format->options == NULL || format->name == NULL)
			/* This format does not support option. */
			continue;
		if (m != NULL) {
			if (strcmp(format->name, m) != 0)
				continue;
			++matched_modules;
		}

		a->format = format;
		r = format->options(a, o, v);
		a->format = NULL;

		if (r == ARCHIVE_FATAL)
			return (ARCHIVE_FATAL);

		if (r == ARCHIVE_OK)
			rv = ARCHIVE_OK;
	}