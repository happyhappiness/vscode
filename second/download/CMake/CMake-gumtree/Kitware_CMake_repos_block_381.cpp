{
			archive_set_error(&a->archive, errno,
			    "Failed to open the data fork for metadata");
			close(tmpfd);
			return (ARCHIVE_WARN);
		}