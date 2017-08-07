{
		archive_set_error(&a->archive, errno,
		    "Failed to restore metadata");
		close(tmpfd);
		tmpfd = -1;
	}