{
			int64_t pos = __archive_read_seek(a, offset, SEEK_SET);
			if (pos == ARCHIVE_FAILED) {
				archive_set_error(&(a->archive),
				    ARCHIVE_ERRNO_MISC,
				    "Cannot seek.");
				return (ARCHIVE_FAILED);
			}
			xar->offset = pos;
		}