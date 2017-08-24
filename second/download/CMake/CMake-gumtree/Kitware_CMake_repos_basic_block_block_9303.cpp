{
			read_buf = a->read_data_block;
			a->read_data_is_posix_read = 1;
			a->read_data_requested = s;
			r = archive_read_data_block(a, &read_buf,
			    &a->read_data_remaining, &a->read_data_offset);
			a->read_data_block = read_buf;
			if (r == ARCHIVE_EOF)
				return (bytes_read);
			/*
			 * Error codes are all negative, so the status
			 * return here cannot be confused with a valid
			 * byte count.  (ARCHIVE_OK is zero.)
			 */
			if (r < ARCHIVE_OK)
				return (r);
		}