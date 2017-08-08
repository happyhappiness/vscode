archive_set_error(&a->archive, en,
		    "Hard-link target '%s' does not exist.",
		    archive_entry_hardlink(a->entry));