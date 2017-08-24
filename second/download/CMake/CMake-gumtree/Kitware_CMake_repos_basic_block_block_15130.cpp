{
		fe = current_fixup(a, archive_entry_pathname_w(entry));
		fe->fixup |= TODO_FFLAGS;
		/* TODO: Complete this.. defer fflags from below. */
	}