(a->st.st_size < a->filesize) {
			const char nul = '\0';
			if (lseek(a->fd, a->filesize - 1, SEEK_SET) < 0) {
				archive_set_error(&a->archive, errno,
				    "Seek failed");
				return (ARCHIVE_FATAL);
			}
			if (write(a->fd, &nul, 1) < 0) {
				archive_set_error(&a->archive, errno,
				    "Write to restore size failed");
				return (ARCHIVE_FATAL);
			}
			a->pst = NULL;
		}