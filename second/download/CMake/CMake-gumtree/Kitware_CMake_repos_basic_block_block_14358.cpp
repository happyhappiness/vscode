(state->avail < state->buffer_size) {
		/* If buffer is not empty... */
		/* ... copy data into buffer ... */
		to_copy = ((size_t)remaining > state->avail) ?
			state->avail : (size_t)remaining;
		memcpy(state->next, buff, to_copy);
		state->next += to_copy;
		state->avail -= to_copy;
		buff += to_copy;
		remaining -= to_copy;
		/* ... if it's full, write it out. */
		if (state->avail == 0) {
			char *p = state->buffer;
			size_t to_write = state->buffer_size;
			while (to_write > 0) {
				bytes_written = (a->client_writer)(&a->archive,
				    a->client_data, p, to_write);
				if (bytes_written <= 0)
					return (ARCHIVE_FATAL);
				if ((size_t)bytes_written > to_write) {
					archive_set_error(&(a->archive),
					    -1, "write overrun");
					return (ARCHIVE_FATAL);
				}
				p += bytes_written;
				to_write -= bytes_written;
			}
			state->next = state->buffer;
			state->avail = state->buffer_size;
		}
	}