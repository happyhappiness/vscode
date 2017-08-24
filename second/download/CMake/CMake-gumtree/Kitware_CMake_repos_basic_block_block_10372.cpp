{
		bytes = child_read(self, p, state->out_buf_len - total);
		if (bytes < 0)
			/* No recovery is possible if we can no longer
			 * read from the child. */
			return (ARCHIVE_FATAL);
		if (bytes == 0)
			/* We got EOF from the child. */
			break;
		total += bytes;
		p += bytes;
	}