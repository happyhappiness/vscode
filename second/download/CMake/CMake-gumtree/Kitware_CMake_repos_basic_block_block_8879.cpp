(r != ARCHIVE_OK) {
					archive_read_free(ar);
					archive_string_free(&as);
					return (r);
				}