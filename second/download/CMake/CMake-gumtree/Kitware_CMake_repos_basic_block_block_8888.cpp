(r == ARCHIVE_EOF) {
			return (ARCHIVE_OK);
		} else {
			archive_copy_error(&(a->archive), ar);
			return (r);
		}