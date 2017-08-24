(en == EEXIST) {
		mode_t st_mode;
		/*
		 * We know something is in the way, but we don't know what;
		 * we need to find out before we go any further.
		 */
		int r = 0;
		/*
		 * The SECURE_SYMLINK logic has already removed a
		 * symlink to a dir if the client wants that.  So
		 * follow the symlink if we're creating a dir.
		 */
		if (S_ISDIR(a->mode))
			r = file_information(a, a->name, &a->st, &st_mode, 0);
		/*
		 * If it's not a dir (or it's a broken symlink),
		 * then don't follow it.
		 */
		if (r != 0 || !S_ISDIR(a->mode))
			r = file_information(a, a->name, &a->st, &st_mode, 1);
		if (r != 0) {
			archive_set_error(&a->archive, errno,
			    "Can't stat existing object");
			return (ARCHIVE_FAILED);
		}

		/*
		 * NO_OVERWRITE_NEWER doesn't apply to directories.
		 */
		if ((a->flags & ARCHIVE_EXTRACT_NO_OVERWRITE_NEWER)
		    &&  !S_ISDIR(st_mode)) {
			if (!older(&(a->st), a->entry)) {
				archive_entry_unset_size(a->entry);
				return (ARCHIVE_OK);
			}
		}

		/* If it's our archive, we're done. */
		if (a->skip_file_set &&
		    bhfi_dev(&a->st) == a->skip_file_dev &&
		    bhfi_ino(&a->st) == a->skip_file_ino) {
			archive_set_error(&a->archive, 0,
			    "Refusing to overwrite archive");
			return (ARCHIVE_FAILED);
		}

		if (!S_ISDIR(st_mode)) {
			/* A non-dir is in the way, unlink it. */
			if (disk_unlink(a->name) != 0) {
				archive_set_error(&a->archive, errno,
				    "Can't unlink already-existing object");
				return (ARCHIVE_FAILED);
			}
			a->pst = NULL;
			/* Try again. */
			en = create_filesystem_object(a);
		} else if (!S_ISDIR(a->mode)) {
			/* A dir is in the way of a non-dir, rmdir it. */
			if (disk_rmdir(a->name) != 0) {
				archive_set_error(&a->archive, errno,
				    "Can't remove already-existing dir");
				return (ARCHIVE_FAILED);
			}
			/* Try again. */
			en = create_filesystem_object(a);
		} else {
			/*
			 * There's a dir in the way of a dir.  Don't
			 * waste time with rmdir()/mkdir(), just fix
			 * up the permissions on the existing dir.
			 * Note that we don't change perms on existing
			 * dirs unless _EXTRACT_PERM is specified.
			 */
			if ((a->mode != st_mode)
			    && (a->todo & TODO_MODE_FORCE))
				a->deferred |= (a->todo & TODO_MODE);
			/* Ownership doesn't need deferred fixup. */
			en = 0; /* Forget the EEXIST. */
		}
	}