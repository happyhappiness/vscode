			en = create_filesystem_object(a);
		} else if (!S_ISDIR(a->mode)) {
			/* A dir is in the way of a non-dir, rmdir it. */
			if (rmdir(a->name) != 0) {
				archive_set_error(&a->archive, errno,
				    "Can't replace existing directory with non-directory");
