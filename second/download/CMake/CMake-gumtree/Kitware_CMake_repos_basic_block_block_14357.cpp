{
			bytes_written = (a->client_writer)(&a->archive,
			    a->client_data, buff, remaining);
			if (bytes_written <= 0)
				return (ARCHIVE_FATAL);
			remaining -= bytes_written;
			buff += bytes_written;
		}