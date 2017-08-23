{
			archive_set_error(&a->archive, errno,
			    "Failed to get ACL permission set");
			return (ARCHIVE_WARN);
		}