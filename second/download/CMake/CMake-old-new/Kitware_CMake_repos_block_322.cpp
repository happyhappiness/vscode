{
					archive_set_error(&a->archive, errno,
					    "Write failed");
					return (ARCHIVE_WARN);
				}