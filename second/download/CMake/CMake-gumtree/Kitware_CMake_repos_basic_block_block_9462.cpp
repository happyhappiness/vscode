(stat(path, &s) != 0) {
				archive_set_error(&a->archive, errno,
				    "Can't stat %s", path);
				return (ARCHIVE_FAILED);
			}