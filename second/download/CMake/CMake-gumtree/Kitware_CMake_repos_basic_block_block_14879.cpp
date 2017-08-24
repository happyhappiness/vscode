(a->fd < 0) {
		/* There's no file. */
	} else if (a->filesize < 0) {
		/* File size is unknown, so we can't set the size. */
	} else if (a->fd_offset == a->filesize) {
		/* Last write ended at exactly the filesize; we're done. */
		/* Hopefully, this is the common case. */
#if defined(__APPLE__) && defined(UF_COMPRESSED) && defined(HAVE_ZLIB_H)
	} else if (a->todo & TODO_HFS_COMPRESSION) {
		char null_d[1024];
		ssize_t r;

		if (a->file_remaining_bytes)
			memset(null_d, 0, sizeof(null_d));
		while (a->file_remaining_bytes) {
			if (a->file_remaining_bytes > sizeof(null_d))
				r = hfs_write_data_block(
				    a, null_d, sizeof(null_d));
			else
				r = hfs_write_data_block(
				    a, null_d, a->file_remaining_bytes);
			if (r < 0)
				return ((int)r);
		}
#endif
	} else {
#if HAVE_FTRUNCATE
		if (ftruncate(a->fd, a->filesize) == -1 &&
		    a->filesize == 0) {
			archive_set_error(&a->archive, errno,
			    "File size could not be restored");
			return (ARCHIVE_FAILED);
		}
#endif
		/*
		 * Not all platforms implement the XSI option to
		 * extend files via ftruncate.  Stat() the file again
		 * to see what happened.
		 */
		a->pst = NULL;
		if ((ret = lazy_stat(a)) != ARCHIVE_OK)
			return (ret);
		/* We can use lseek()/write() to extend the file if
		 * ftruncate didn't work or isn't available. */
		if (a->st.st_size < a->filesize) {
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
	}