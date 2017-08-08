{
				archive_set_error(&a->archive, errno,
				    "Can't remove already-existing dir");
				return (ARCHIVE_FAILED);
			}