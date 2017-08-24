{
		cancel_async(t);
		close_and_restore_time(t->entry_fh, t, &t->restore_time);
		t->entry_fh = INVALID_HANDLE_VALUE;
	}