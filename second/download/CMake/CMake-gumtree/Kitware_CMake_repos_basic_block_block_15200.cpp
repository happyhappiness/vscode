(!S_ISDIR(a->mode)) {
			/* A dir is in the way of a non-dir, rmdir it. */
			if (disk_rmdir(a->name) != 0) {
				archive_set_error(&a->archive, errno,
				    "Can't remove already-existing dir");
				return (ARCHIVE_FAILED);
			}
			/* Try again. */
			en = create_filesystem_object(a);
		}