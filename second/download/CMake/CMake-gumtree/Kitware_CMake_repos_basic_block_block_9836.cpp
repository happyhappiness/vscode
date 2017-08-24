(t->entry_fd >= 0) {
		close_and_restore_time(t->entry_fd, t, &t->restore_time);
		t->entry_fd = -1;
	}