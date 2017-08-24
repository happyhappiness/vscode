{
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