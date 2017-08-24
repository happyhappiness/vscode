(lseek(a->fd, a->filesize - 1, SEEK_SET) < 0) {
				archive_set_error(&a->archive, errno,
				    "Seek failed");
				return (ARCHIVE_FATAL);
			}