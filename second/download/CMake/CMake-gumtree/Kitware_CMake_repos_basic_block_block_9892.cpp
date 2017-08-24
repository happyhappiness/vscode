{
		cancel_async(t);
		/* Close the current file descriptor */
		close_and_restore_time(t->entry_fh, t, &t->restore_time);
		t->entry_fh = INVALID_HANDLE_VALUE;
	}