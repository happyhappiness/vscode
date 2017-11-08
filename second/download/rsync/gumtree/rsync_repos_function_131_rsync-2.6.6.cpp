static int keep_backup(char *fname)
{
	STRUCT_STAT st;
	struct file_struct *file;
	char *buf;
	int kept = 0;
	int ret_code;

	/* return if no file to keep */
	if (do_lstat(fname, &st) < 0)
		return 1;

	if (!(file = make_file(fname, NULL, NO_FILTERS)))
		return 1; /* the file could have disappeared */

	if (!(buf = get_backup_name(fname)))
		return 0;

	/* Check to see if this is a device file, or link */
	if (IS_DEVICE(file->mode) && am_root && preserve_devices) {
		do_unlink(buf);
		if (do_mknod(buf, file->mode, file->u.rdev) < 0
		    && (errno != ENOENT || make_bak_dir(buf) < 0
		     || do_mknod(buf, file->mode, file->u.rdev) < 0)) {
			rsyserr(FERROR, errno, "mknod %s failed",
				full_fname(buf));
		} else if (verbose > 2) {
			rprintf(FINFO, "make_backup: DEVICE %s successful.\n",
				safe_fname(fname));
		}
		kept = 1;
		do_unlink(fname);
	}

	if (!kept && S_ISDIR(file->mode)) {
		/* make an empty directory */
		if (do_mkdir(buf, file->mode) < 0
		    && (errno != ENOENT || make_bak_dir(buf) < 0
		     || do_mkdir(buf, file->mode) < 0)) {
			rsyserr(FINFO, errno, "mkdir %s failed",
				full_fname(buf));
		}

		ret_code = do_rmdir(fname);
		if (verbose > 2) {
			rprintf(FINFO, "make_backup: RMDIR %s returns %i\n",
				full_fname(fname), ret_code);
		}
		kept = 1;
	}

#ifdef SUPPORT_LINKS
	if (!kept && preserve_links && S_ISLNK(file->mode)) {
		if (safe_symlinks && unsafe_symlink(file->u.link, buf)) {
			if (verbose) {
				rprintf(FINFO, "ignoring unsafe symlink %s -> %s\n",
					full_fname(buf), file->u.link);
			}
			kept = 1;
		} else {
			do_unlink(buf);
			if (do_symlink(file->u.link, buf) < 0
			    && (errno != ENOENT || make_bak_dir(buf) < 0
			     || do_symlink(file->u.link, buf) < 0)) {
				rsyserr(FERROR, errno, "link %s -> \"%s\"",
					full_fname(buf),
					safe_fname(file->u.link));
			}
			do_unlink(fname);
			kept = 1;
		}
	}
#endif

	if (!kept && !S_ISREG(file->mode)) {
		rprintf(FINFO, "make_bak: skipping non-regular file %s\n",
			safe_fname(fname));
		return 1;
	}

	/* move to keep tree if a file */
	if (!kept) {
		if (robust_move(fname, buf) != 0) {
			rsyserr(FERROR, errno, "keep_backup failed: %s -> \"%s\"",
				full_fname(fname), safe_fname(buf));
		} else if (st.st_nlink > 1) {
			/* If someone has hard-linked the file into the backup
			 * dir, rename() might return success but do nothing! */
			robust_unlink(fname); /* Just in case... */
		}
	}
	set_perms(buf, file, NULL, 0);
	free(file);

	if (verbose > 1) {
		rprintf(FINFO, "backed up %s to %s\n",
			safe_fname(fname), safe_fname(buf));
	}
	return 1;
}