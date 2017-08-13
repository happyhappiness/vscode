{
		t->current_filesystem->synthetic = -1;
		t->current_filesystem->remote = -1;
		archive_set_error(&a->archive, errno, "statfs failed");
		return (ARCHIVE_FAILED);
	}