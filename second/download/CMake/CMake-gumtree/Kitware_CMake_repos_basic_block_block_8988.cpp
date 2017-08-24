(f->ctime_sec > sec) {
			if (f->flag & ARCHIVE_MATCH_OLDER)
				return (1);
		} else if (f->ctime_sec < sec) {
			if (f->flag & ARCHIVE_MATCH_NEWER)
				return (1);
		} else {
			nsec = archive_entry_ctime_nsec(entry);
			if (f->ctime_nsec > nsec) {
				if (f->flag & ARCHIVE_MATCH_OLDER)
					return (1);
			} else if (f->ctime_nsec < nsec) {
				if (f->flag & ARCHIVE_MATCH_NEWER)
					return (1);
			} else if (f->flag & ARCHIVE_MATCH_EQUAL)
				return (1);
		}