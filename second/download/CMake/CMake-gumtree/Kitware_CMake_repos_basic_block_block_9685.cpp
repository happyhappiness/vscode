{
		/* Close the current file descriptor */
		close_and_restore_time(t->entry_fd, t, &t->restore_time);
		t->entry_fd = -1;
		t->entry_eof = 1;
	}