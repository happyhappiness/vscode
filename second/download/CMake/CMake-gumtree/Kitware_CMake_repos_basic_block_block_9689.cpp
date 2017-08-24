(buffbytes > 0) {
		bytes = read(t->entry_fd, t->entry_buff, buffbytes);
		if (bytes < 0) {
			archive_set_error(&a->archive, errno, "Read error");
			r = ARCHIVE_FATAL;
			a->archive.state = ARCHIVE_STATE_FATAL;
			goto abort_read_data;
		}
	} else
		bytes = 0