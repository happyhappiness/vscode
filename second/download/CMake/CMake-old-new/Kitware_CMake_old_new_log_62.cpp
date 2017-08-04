archive_set_error(&a->archive, errno,
					    "Could not remove symlink %s",
					    a->name)