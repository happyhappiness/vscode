(a->flags & ARCHIVE_READDISK_NO_TRAVERSE_MOUNTS) {
		if (t->initial_filesystem_id != t->current_filesystem_id)
			descend = 0;
	}