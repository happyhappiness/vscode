(filter = a->filter_first; filter != NULL; filter = filter->next_filter) {
		if (filter->options == NULL)
			continue;
		if (m != NULL && strcmp(filter->name, m) != 0)
			continue;

		r = filter->options(filter, o, v);

		if (r == ARCHIVE_FATAL)
			return (ARCHIVE_FATAL);

		if (m != NULL)
			return (r);

		if (r == ARCHIVE_OK)
			rv = ARCHIVE_OK;
	}