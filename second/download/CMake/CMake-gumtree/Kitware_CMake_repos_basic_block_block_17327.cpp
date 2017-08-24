(archive_entry_hardlink(file->entry) != NULL) {
			archive_entry_unset_size(file->entry);
			return (r2);
		}