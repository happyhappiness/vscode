{
		bytes_to_write = size;
		/* Seek if necessary to the specified offset. */
		if (a->offset < a->fd_offset) {
			/* Can't support backward move. */
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Seek failed");
			return (ARCHIVE_FATAL);
		} else if (a->offset > a->fd_offset) {
			int64_t skip = a->offset - a->fd_offset;
			char nullblock[1024];

			memset(nullblock, 0, sizeof(nullblock));
			while (skip > 0) {
				if (skip > (int64_t)sizeof(nullblock))
					bytes_written = hfs_write_decmpfs_block(
					    a, nullblock, sizeof(nullblock));
				else
					bytes_written = hfs_write_decmpfs_block(
					    a, nullblock, skip);
				if (bytes_written < 0) {
					archive_set_error(&a->archive, errno,
					    "Write failed");
					return (ARCHIVE_WARN);
				}
				skip -= bytes_written;
			}

			a->fd_offset = a->offset;
		}
		bytes_written =
		    hfs_write_decmpfs_block(a, buff, bytes_to_write);
		if (bytes_written < 0)
			return (bytes_written);
		buff += bytes_written;
		size -= bytes_written;
		a->total_bytes_written += bytes_written;
		a->offset += bytes_written;
		a->fd_offset = a->offset;
	}