{
			if (total == 0 && ravail <= 0) {
				/* There is nothing more to read, fail */
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Missing format data");
				return (ARCHIVE_FATAL);
			}
			/*
			 * Save remaining data which does not contain
			 * NL('\n','\r').
			 */
			if (ensure_in_buff_size(self, uudecode, len)
			    != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			if (uudecode->in_buff != b)
				memmove(uudecode->in_buff, b, len);
			uudecode->in_cnt = (int)len;
			if (total == 0) {
				/* Do not return 0; it means end-of-file.
				 * We should try to read bytes more. */
				__archive_read_filter_consume(
				    self->upstream, ravail);
				goto read_more;
			}
			used += len;
			break;
		}