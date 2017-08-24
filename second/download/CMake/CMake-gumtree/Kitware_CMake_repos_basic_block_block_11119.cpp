((p = __archive_read_ahead(a, used+256, NULL)) == NULL)
			return (truncated_error(a));