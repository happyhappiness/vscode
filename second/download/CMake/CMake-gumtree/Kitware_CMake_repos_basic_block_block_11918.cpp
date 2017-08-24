((p = __archive_read_ahead(a, sizeof(*p), NULL)) == NULL)
			return (truncated_error(a));