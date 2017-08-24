(step > 0) {
			step = __archive_read_consume(a, step);
			if (step < 0)
				return ((int)step);
			xar->offset += step;
		} else {
			int64_t pos = __archive_read_seek(a, offset, SEEK_SET);
			if (pos == ARCHIVE_FAILED) {
				archive_set_error(&(a->archive),
				    ARCHIVE_ERRNO_MISC,
				    "Cannot seek.");
				return (ARCHIVE_FAILED);
			}
			xar->offset = pos;
		}