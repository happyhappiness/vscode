{
		/* Write out full blocks directly to client. */
		bytes_written = (a->client_writer)(&a->archive,
		    a->client_data, buff, state->buffer_size);
		if (bytes_written <= 0)
			return (ARCHIVE_FATAL);
		buff += bytes_written;
		remaining -= bytes_written;
	}