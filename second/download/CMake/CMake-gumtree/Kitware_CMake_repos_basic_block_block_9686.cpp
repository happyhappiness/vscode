{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct tree *t = a->tree;
	int r;
	ssize_t bytes;
	size_t buffbytes;
	int empty_sparse_region = 0;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC, ARCHIVE_STATE_DATA,
	    "archive_read_data_block");

	if (t->entry_eof || t->entry_remaining_bytes <= 0) {
		r = ARCHIVE_EOF;
		goto abort_read_data;
	}

	/*
	 * Open the current file.
	 */
	if (t->entry_fd < 0) {
		int flags = O_RDONLY | O_BINARY | O_CLOEXEC;

		/*
		 * Eliminate or reduce cache effects if we can.
		 *
		 * Carefully consider this to be enabled.
		 */
#if defined(O_DIRECT) && 0/* Disabled for now */
		if (t->current_filesystem->xfer_align != -1 &&
		    t->nlink == 1)
			flags |= O_DIRECT;
#endif
#if defined(O_NOATIME)
		/*
		 * Linux has O_NOATIME flag; use it if we need.
		 */
		if ((t->flags & needsRestoreTimes) != 0 &&
		    t->restore_time.noatime == 0)
			flags |= O_NOATIME;
		do {
#endif
			t->entry_fd = open_on_current_dir(t,
			    tree_current_access_path(t), flags);
			__archive_ensure_cloexec_flag(t->entry_fd);
#if defined(O_NOATIME)
			/*
			 * When we did open the file with O_NOATIME flag,
			 * if successful, set 1 to t->restore_time.noatime
			 * not to restore an atime of the file later.
			 * if failed by EPERM, retry it without O_NOATIME flag.
			 */
			if (flags & O_NOATIME) {
				if (t->entry_fd >= 0)
					t->restore_time.noatime = 1;
				else if (errno == EPERM) {
					flags &= ~O_NOATIME;
					continue;
				}
			}
		} while (0);
#endif
		if (t->entry_fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Couldn't open %s", tree_current_path(t));
			r = ARCHIVE_FAILED;
			tree_enter_initial_dir(t);
			goto abort_read_data;
		}
		tree_enter_initial_dir(t);
	}

	/*
	 * Allocate read buffer if not allocated.
	 */
	if (t->current_filesystem->allocation_ptr == NULL) {
		r = setup_suitable_read_buffer(a);
		if (r != ARCHIVE_OK) {
			a->archive.state = ARCHIVE_STATE_FATAL;
			goto abort_read_data;
		}
	}
	t->entry_buff = t->current_filesystem->buff;
	t->entry_buff_size = t->current_filesystem->buff_size;

	buffbytes = t->entry_buff_size;
	if ((int64_t)buffbytes > t->current_sparse->length)
		buffbytes = t->current_sparse->length;

	if (t->current_sparse->length == 0)
		empty_sparse_region = 1;

	/*
	 * Skip hole.
	 * TODO: Should we consider t->current_filesystem->xfer_align?
	 */
	if (t->current_sparse->offset > t->entry_total) {
		if (lseek(t->entry_fd,
		    (off_t)t->current_sparse->offset, SEEK_SET) < 0) {
			archive_set_error(&a->archive, errno, "Seek error");
			r = ARCHIVE_FATAL;
			a->archive.state = ARCHIVE_STATE_FATAL;
			goto abort_read_data;
		}
		bytes = t->current_sparse->offset - t->entry_total;
		t->entry_remaining_bytes -= bytes;
		t->entry_total += bytes;
	}

	/*
	 * Read file contents.
	 */
	if (buffbytes > 0) {
		bytes = read(t->entry_fd, t->entry_buff, buffbytes);
		if (bytes < 0) {
			archive_set_error(&a->archive, errno, "Read error");
			r = ARCHIVE_FATAL;
			a->archive.state = ARCHIVE_STATE_FATAL;
			goto abort_read_data;
		}
	} else
		bytes = 0;
	/*
	 * Return an EOF unless we've read a leading empty sparse region, which
	 * is used to represent fully-sparse files.
	*/
	if (bytes == 0 && !empty_sparse_region) {
		/* Get EOF */
		t->entry_eof = 1;
		r = ARCHIVE_EOF;
		goto abort_read_data;
	}
	*buff = t->entry_buff;
	*size = bytes;
	*offset = t->entry_total;
	t->entry_total += bytes;
	t->entry_remaining_bytes -= bytes;
	if (t->entry_remaining_bytes == 0) {
		/* Close the current file descriptor */
		close_and_restore_time(t->entry_fd, t, &t->restore_time);
		t->entry_fd = -1;
		t->entry_eof = 1;
	}
	t->current_sparse->offset += bytes;
	t->current_sparse->length -= bytes;
	if (t->current_sparse->length == 0 && !t->entry_eof)
		t->current_sparse++;
	return (ARCHIVE_OK);

abort_read_data:
	*buff = NULL;
	*size = 0;
	*offset = t->entry_total;
	if (t->entry_fd >= 0) {
		/* Close the current file descriptor */
		close_and_restore_time(t->entry_fd, t, &t->restore_time);
		t->entry_fd = -1;
	}
	return (r);
}