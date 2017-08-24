(t->ol_num_doing == 0) {
		do {
			r = start_next_async_read(a, t);
			if (r == ARCHIVE_FATAL)
				goto abort_read_data;
			if (!t->async_io)
				break;
		} while (r == ARCHIVE_OK && t->ol_num_doing < MAX_OVERLAPPED);
	} else {
		if (start_next_async_read(a, t) == ARCHIVE_FATAL)
			goto abort_read_data;
	}