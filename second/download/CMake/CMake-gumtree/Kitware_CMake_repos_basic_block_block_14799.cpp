{
			bytes_written = write(a->fd, b, bytes_to_write);
			if (bytes_written < 0) {
				archive_set_error(&a->archive, errno,
				    "Write failed");
				return (ARCHIVE_WARN);
			}
			bytes_to_write -= bytes_written;
			b += bytes_written;
		}