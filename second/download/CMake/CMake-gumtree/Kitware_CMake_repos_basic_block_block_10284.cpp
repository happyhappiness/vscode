{
			unsigned int checksum;
			unsigned int checksum_stream;
			read_buf = __archive_read_filter_ahead(self->upstream,
			    4, &bytes_remaining);
			if (read_buf == NULL) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC, "truncated lz4 input");
				return (ARCHIVE_FATAL);
			}
			checksum = archive_le32dec(read_buf);
			__archive_read_filter_consume(self->upstream, 4);
			checksum_stream = __archive_xxhash.XXH32_digest(
			    state->xxh32_state);
			state->xxh32_state = NULL;
			if (checksum != checksum_stream) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "lz4 stream cheksum error");
				return (ARCHIVE_FATAL);
			}
		}