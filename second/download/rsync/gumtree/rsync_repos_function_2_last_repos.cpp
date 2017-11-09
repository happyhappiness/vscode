enum delret delete_item(char *fbuf, uint16 mode, uint16 flags)
{
	enum delret ret;
	char *what;
	int ok;

	if (DEBUG_GTE(DEL, 2)) {
		rprintf(FINFO, "delete_item(%s) mode=%o flags=%d\n",
			fbuf, (int)mode, (int)flags);
	}

	if (flags & DEL_NO_UID_WRITE)
		do_chmod(fbuf, mode | S_IWUSR);

	if (S_ISDIR(mode) && !(flags & DEL_DIR_IS_EMPTY)) {
		/* This only happens on the first call to delete_item() since
		 * delete_dir_contents() always calls us w/DEL_DIR_IS_EMPTY. */
		ignore_perishable = 1;
		/* If DEL_RECURSE is not set, this just reports emptiness. */
		ret = delete_dir_contents(fbuf, flags);
		ignore_perishable = 0;
		if (ret == DR_NOT_EMPTY || ret == DR_AT_LIMIT)
			goto check_ret;
		/* OK: try to delete the directory. */
	}

	if (!(flags & DEL_MAKE_ROOM) && max_delete >= 0 && stats.deleted_files >= max_delete) {
		skipped_deletes++;
		return DR_AT_LIMIT;
	}

	if (S_ISDIR(mode)) {
		what = "rmdir";
		ok = do_rmdir(fbuf) == 0;
	} else {
		if (make_backups > 0 && !(flags & DEL_FOR_BACKUP) && (backup_dir || !is_backup_file(fbuf))) {
			what = "make_backup";
			ok = make_backup(fbuf, True);
			if (ok == 2) {
				what = "unlink";
				ok = robust_unlink(fbuf) == 0;
			}
		} else {
			what = "unlink";
			ok = robust_unlink(fbuf) == 0;
		}
	}

	if (ok) {
		if (!(flags & DEL_MAKE_ROOM)) {
			log_delete(fbuf, mode);
			stats.deleted_files++;
			if (S_ISREG(mode)) {
				/* Nothing more to count */
			} else if (S_ISDIR(mode))
				stats.deleted_dirs++;
#ifdef SUPPORT_LINKS
			else if (S_ISLNK(mode))
				stats.deleted_symlinks++;
#endif
			else if (IS_DEVICE(mode))
				stats.deleted_symlinks++;
			else
				stats.deleted_specials++;
		}
		ret = DR_SUCCESS;
	} else {
		if (S_ISDIR(mode) && errno == ENOTEMPTY) {
			rprintf(FINFO, "cannot delete non-empty directory: %s\n",
				fbuf);
			ret = DR_NOT_EMPTY;
		} else if (errno != ENOENT) {
			rsyserr(FERROR_XFER, errno, "delete_file: %s(%s) failed",
				what, fbuf);
			ret = DR_FAILURE;
		} else
			ret = DR_SUCCESS;
	}

  check_ret:
	if (ret != DR_SUCCESS && flags & DEL_MAKE_ROOM) {
		const char *desc;
		switch (flags & DEL_MAKE_ROOM) {
		case DEL_FOR_FILE: desc = "regular file"; break;
		case DEL_FOR_DIR: desc = "directory"; break;
		case DEL_FOR_SYMLINK: desc = "symlink"; break;
		case DEL_FOR_DEVICE: desc = "device file"; break;
		case DEL_FOR_SPECIAL: desc = "special file"; break;
		default: exit_cleanup(RERR_UNSUPPORTED); /* IMPOSSIBLE */
		}
		rprintf(FERROR_XFER, "could not make way for %s %s: %s\n",
			flags & DEL_FOR_BACKUP ? "backup" : "new",
			desc, fbuf);
	}
	return ret;
}