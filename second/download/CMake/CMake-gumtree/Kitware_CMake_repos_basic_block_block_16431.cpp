(np->virtual &&
		    !archive_entry_mtime_is_set(np->file->entry)) {
			/* Set properly times to virtual directory */
			archive_entry_set_mtime(np->file->entry,
			    iso9660->birth_time, 0);
			archive_entry_set_atime(np->file->entry,
			    iso9660->birth_time, 0);
			archive_entry_set_ctime(np->file->entry,
			    iso9660->birth_time, 0);
		}