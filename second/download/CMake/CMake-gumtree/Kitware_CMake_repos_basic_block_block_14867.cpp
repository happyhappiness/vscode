{
		a->uid = archive_write_disk_uid(&a->archive,
		    archive_entry_uname(a->entry),
		    archive_entry_uid(a->entry));
	}