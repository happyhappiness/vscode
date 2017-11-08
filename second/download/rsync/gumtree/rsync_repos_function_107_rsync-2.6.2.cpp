static int keep_backup(char *fname)
{
	STRUCT_STAT st;
	struct file_struct *file;
	int kept = 0;
	int ret_code;

	/* return if no file to keep */
#if SUPPORT_LINKS
	if (do_lstat(fname, &st)) return 1;
#else
	if (do_stat(fname, &st)) return 1;
#endif

	file = make_file(fname, NULL, NO_EXCLUDES);

	/* the file could have disappeared */
	if (!file) return 1;

	/* make a complete pathname for backup file */
	if (stringjoin(backup_dir_buf + backup_dir_len, backup_dir_remainder,
	    fname, backup_suffix, NULL) >= backup_dir_remainder) {
		rprintf(FERROR, "keep_backup filename too long\n");
		return 0;
	}

#ifdef HAVE_MKNOD
	/* Check to see if this is a device file, or link */
	if (IS_DEVICE(file->mode)) {
		if (am_root && preserve_devices) {
			make_bak_dir(backup_dir_buf);
			if (do_mknod(backup_dir_buf, file->mode, file->u.rdev) != 0) {
				rprintf(FERROR, "mknod %s failed: %s\n",
					full_fname(backup_dir_buf), strerror(errno));
			} else if (verbose > 2) {
				rprintf(FINFO,
					"make_backup: DEVICE %s successful.\n",
					fname);
			}
		}
		kept = 1;
		do_unlink(fname);
	}
#endif

	if (!kept && S_ISDIR(file->mode)) {
		/* make an empty directory */
		make_bak_dir(backup_dir_buf);
		do_mkdir(backup_dir_buf, file->mode);
		ret_code = do_rmdir(fname);

		if (verbose > 2) {
			rprintf(FINFO, "make_backup: RMDIR %s returns %i\n",
				full_fname(fname), ret_code);
		}
		kept = 1;
	}

#if SUPPORT_LINKS
	if (!kept && preserve_links && S_ISLNK(file->mode)) {
		extern int safe_symlinks;
		if (safe_symlinks && unsafe_symlink(file->u.link, backup_dir_buf)) {
			if (verbose) {
				rprintf(FINFO, "ignoring unsafe symlink %s -> %s\n",
					full_fname(backup_dir_buf), file->u.link);
			}
			kept = 1;
		}
		make_bak_dir(backup_dir_buf);
		if (do_symlink(file->u.link, backup_dir_buf) != 0) {
			rprintf(FERROR, "link %s -> %s : %s\n",
				full_fname(backup_dir_buf), file->u.link, strerror(errno));
		}
		do_unlink(fname);
		kept = 1;
	}
#endif

	if (!kept && !S_ISREG(file->mode)) {
		rprintf(FINFO, "make_bak: skipping non-regular file %s\n",
			fname);
	}

	/* move to keep tree if a file */
	if (!kept) {
		if (robust_move(fname, backup_dir_buf) != 0) {
			rprintf(FERROR, "keep_backup failed: %s -> \"%s\": %s\n",
				full_fname(fname), backup_dir_buf, strerror(errno));
		}
	}
	set_perms(backup_dir_buf, file, NULL, 0);
	free(file);

	if (verbose > 1)
		rprintf(FINFO, "keep_backup %s -> %s\n", fname, backup_dir_buf);
	return 1;
}