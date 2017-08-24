(total == 0) {
				/* Do not return 0; it means end-of-file.
				 * We should try to read bytes more. */
				__archive_read_filter_consume(
				    self->upstream, ravail);
				goto read_more;
			}