(disk_unlink(path) != 0) {
			archive_set_error(&a->archive, errno,
			    "Can't create directory '%ls': "
			    "Conflicting file cannot be removed",
			    path);
			return (ARCHIVE_FAILED);
		}