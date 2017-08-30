
	tar = (struct tar *)(a->format->data);

	for (;;) {
		/* Remove exhausted entries from sparse list. */
		while (tar->sparse_list != NULL &&
		    tar->sparse_list->remaining == 0) {
			p = tar->sparse_list;
			tar->sparse_list = p->next;
			free(p);
		}

		if (tar->entry_bytes_unconsumed) {
			__archive_read_consume(a, tar->entry_bytes_unconsumed);
			tar->entry_bytes_unconsumed = 0;
		}

		/* If we're at end of file, return EOF. */
		if (tar->sparse_list == NULL ||
		    tar->entry_bytes_remaining == 0) {
			if (__archive_read_consume(a, tar->entry_padding) < 0)
				return (ARCHIVE_FATAL);
			tar->entry_padding = 0;
			*buff = NULL;
			*size = 0;
			*offset = tar->realsize;
			return (ARCHIVE_EOF);
		}

		*buff = __archive_read_ahead(a, 1, &bytes_read);
		if (bytes_read < 0)
			return (ARCHIVE_FATAL);
		if (*buff == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Truncated tar archive");
			return (ARCHIVE_FATAL);
		}
		if (bytes_read > tar->entry_bytes_remaining)
			bytes_read = (ssize_t)tar->entry_bytes_remaining;
		/* Don't read more than is available in the
		 * current sparse block. */
		if (tar->sparse_list->remaining < bytes_read)
			bytes_read = (ssize_t)tar->sparse_list->remaining;
		*size = bytes_read;
		*offset = tar->sparse_list->offset;
		tar->sparse_list->remaining -= bytes_read;
		tar->sparse_list->offset += bytes_read;
		tar->entry_bytes_remaining -= bytes_read;
		tar->entry_bytes_unconsumed = bytes_read;

		if (!tar->sparse_list->hole)
			return (ARCHIVE_OK);
		/* Current is hole data and skip this. */
	}
}

static int
