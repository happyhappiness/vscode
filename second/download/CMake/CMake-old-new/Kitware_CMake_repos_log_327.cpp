archive_set_error(&a->archive, errno,
			    "Can't create directory '%s': "
			    "Conflicting file cannot be removed",
			    path);