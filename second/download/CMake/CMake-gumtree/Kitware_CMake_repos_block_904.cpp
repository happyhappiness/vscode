{
			archive_set_error(&a->archive, errno,
			    "Failed to get ACL tag type");
			return (ARCHIVE_WARN);
		}