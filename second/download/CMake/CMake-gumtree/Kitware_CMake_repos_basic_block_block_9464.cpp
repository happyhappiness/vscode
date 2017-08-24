(!a->follow_symlinks) {
				if (lstat(path, &s) != 0) {
					archive_set_error(&a->archive, errno,
					    "Can't lstat %s", path);
					return (ARCHIVE_FAILED);
				}
			}