(algsize > 0) {
			if (lseek(xar->temp_fd, algsize, SEEK_SET) < 0) {
				archive_set_error(&(a->archive), errno,
				    "lseek failed");
				return (ARCHIVE_FATAL);
			}
			xar->temp_offset = algsize;
		}