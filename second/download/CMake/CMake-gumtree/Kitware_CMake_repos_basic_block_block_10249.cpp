{
			read_buf = __archive_read_filter_ahead(
				self->upstream, 4, NULL);
			if (read_buf == NULL) {
				archive_set_error(
				    &self->archive->archive,
		    		    ARCHIVE_ERRNO_MISC,
				    "Malformed lz4 data");
				return (ARCHIVE_FATAL);
			}
			uint32_t skip_bytes = archive_le32dec(read_buf);
			__archive_read_filter_consume(self->upstream,
				4 + skip_bytes);
		}