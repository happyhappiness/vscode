{
		fe = current_fixup(a, archive_entry_pathname(entry));
		if (fe == NULL)
			return (ARCHIVE_FATAL);
		fe->fixup |= TODO_FFLAGS;
		/* TODO: Complete this.. defer fflags from below. */
	}