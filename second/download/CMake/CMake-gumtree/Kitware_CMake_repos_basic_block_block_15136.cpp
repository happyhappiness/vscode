{
		fe = current_fixup(a, archive_entry_pathname_w(entry));
		fe->fixup |= TODO_MODE_BASE;
		fe->mode = a->mode;
	}