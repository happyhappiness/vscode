static int keep_backup(const char *fname)
{
	stat_x sx;
	struct file_struct *file;
	char *buf;
	int save_preserve_xattrs = preserve_xattrs;
	int kept = 0;
	int ret_code;

	/* return if no file to keep */
	if (x_lstat(fname, &sx.st, NULL) < 0)
		return 1;
#ifdef SUPPORT_ACLS
	sx.acc_acl = sx.def_acl = NULL;
#endif
#ifdef SUPPORT_XATTRS
	sx.xattr = NULL;
#endif

	if (!(file = make_file(fname, NULL, NULL, 0, NO_FILTERS)))
		return 1; /* the file could have disappeared */

	if (!(buf = get_backup_name(fname))) {
		unmake_file(file);
		return 0;
	}

#ifdef SUPPORT_ACLS
	if (preserve_acls && !S_ISLNK(file->mode)) {
		get_acl(fname, &sx);
		cache_acl(file, &sx);
		free_acl(&sx);
	}
#endif
#ifdef SUPPORT_XATTRS
	if (preserve_xattrs) {
		get_xattr(fname, &sx);
		cache_xattr(file, &sx);
		free_xattr(&sx);
	}
#endif

	/* Check to see if this is a device file, or link */
	if ((am_root && preserve_devices && IS_DEVICE(file->mode))
	 || (preserve_specials && IS_SPECIAL(file->mode))) {
		int save_errno;
		do_unlink(buf);
		if (do_mknod(buf, file->mode, sx.st.st_rdev) < 0) {
			save_errno = errno ? errno : EINVAL; /* 0 paranoia */
			if (errno == ENOENT && make_bak_dir(buf) == 0) {
				if (do_mknod(buf, file->mode, sx.st.st_rdev) < 0)
					save_errno = errno ? errno : save_errno;
				else
					save_errno = 0;
			}
			if (save_errno) {
				rsyserr(FERROR, save_errno, "mknod %s failed",
					full_fname(buf));
			}
		} else
			save_errno = 0;
		if (verbose > 2 && save_errno == 0) {
			rprintf(FINFO, "make_backup: DEVICE %s successful.\n",
				fname);
		}
		kept = 1;
		do_unlink(fname);
	}

	if (!kept && S_ISDIR(file->mode)) {
		/* make an empty directory */
		if (do_mkdir(buf, file->mode) < 0) {
			int save_errno = errno ? errno : EINVAL; /* 0 paranoia */
			if (errno == ENOENT && make_bak_dir(buf) == 0) {
				if (do_mkdir(buf, file->mode) < 0)
					save_errno = errno ? errno : save_errno;
				else
					save_errno = 0;
			}
			if (save_errno) {
				rsyserr(FINFO, save_errno, "mkdir %s failed",
					full_fname(buf));
			}
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
		const char *sl = F_SYMLINK(file);
		if (safe_symlinks && unsafe_symlink(sl, buf)) {
			if (verbose) {
				rprintf(FINFO, "ignoring unsafe symlink %s -> %s\n",
					full_fname(buf), sl);
			}
			kept = 1;
		} else {
			do_unlink(buf);
			if (do_symlink(sl, buf) < 0) {
				int save_errno = errno ? errno : EINVAL; /* 0 paranoia */
				if (errno == ENOENT && make_bak_dir(buf) == 0) {
					if (do_symlink(sl, buf) < 0)
						save_errno = errno ? errno : save_errno;
					else
						save_errno = 0;
				}
				if (save_errno) {
					rsyserr(FERROR, save_errno, "link %s -> \"%s\"",
						full_fname(buf), sl);
				}
			}
			do_unlink(fname);
			kept = 1;
		}
	}
#endif

	if (!kept && !S_ISREG(file->mode)) {
		rprintf(FINFO, "make_bak: skipping non-regular file %s\n",
			fname);
		unmake_file(file);
		return 1;
	}

	/* move to keep tree if a file */
	if (!kept) {
		if (robust_move(fname, buf) != 0) {
			rsyserr(FERROR, errno, "keep_backup failed: %s -> \"%s\"",
				full_fname(fname), buf);
		} else if (sx.st.st_nlink > 1) {
			/* If someone has hard-linked the file into the backup
			 * dir, rename() might return success but do nothing! */
			robust_unlink(fname); /* Just in case... */
		}
	}
	preserve_xattrs = 0;
	set_file_attrs(buf, file, NULL, fname, 0);
	preserve_xattrs = save_preserve_xattrs;
	unmake_file(file);

	if (verbose > 1) {
		rprintf(FINFO, "backed up %s to %s\n",
			fname, buf);
	}
	return 1;
}