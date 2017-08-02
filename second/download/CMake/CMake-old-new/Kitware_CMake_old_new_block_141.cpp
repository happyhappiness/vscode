{
		t->current_filesystem->remote = -1;
		archive_set_error(&a->archive, errno, "statvfs failed");
		return (ARCHIVE_FAILED);
	}