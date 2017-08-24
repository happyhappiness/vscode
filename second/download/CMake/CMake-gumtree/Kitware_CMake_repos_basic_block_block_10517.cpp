(state->stream.next_in == NULL && avail_in < 0) {
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "truncated input");
			return (ARCHIVE_FATAL);
		}