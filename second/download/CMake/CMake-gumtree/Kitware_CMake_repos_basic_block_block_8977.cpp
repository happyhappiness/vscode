(f->mtime_sec < sec) {
			if (f->flag & ARCHIVE_MATCH_NEWER)
				return (1);
		}