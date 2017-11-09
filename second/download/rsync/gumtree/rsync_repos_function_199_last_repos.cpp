int make_backup(const char *fname, BOOL prefer_rename)
{
	stat_x sx;
	struct file_struct *file;
	int save_preserve_xattrs;
	char *buf;
	int ret = 0;

	init_stat_x(&sx);
	/* Return success if no file to keep. */
	if (x_lstat(fname, &sx.st, NULL) < 0)
		return 3;

	if (!(buf = get_backup_name(fname)))
		return 0;

	/* Try a hard-link or a rename first.  Using rename is not atomic, but
	 * is more efficient than forcing a copy for larger files when no hard-
	 * linking is possible. */
	if ((ret = link_or_rename(fname, buf, prefer_rename, &sx.st)) != 0)
		goto success;
	if (errno == EEXIST || errno == EISDIR) {
		STRUCT_STAT bakst;
		if (do_lstat(buf, &bakst) == 0) {
			int flags = get_del_for_flag(bakst.st_mode) | DEL_FOR_BACKUP | DEL_RECURSE;
			if (delete_item(buf, bakst.st_mode, flags) != 0)
				return 0;
		}
		if ((ret = link_or_rename(fname, buf, prefer_rename, &sx.st)) != 0)
			goto success;
	}

	/* Fall back to making a copy. */
	if (!(file = make_file(fname, NULL, &sx.st, 0, NO_FILTERS)))
		return 3; /* the file could have disappeared */

#ifdef SUPPORT_ACLS
	if (preserve_acls && !S_ISLNK(file->mode)) {
		get_acl(fname, &sx);
		cache_tmp_acl(file, &sx);
		free_acl(&sx);
	}
#endif
#ifdef SUPPORT_XATTRS
	if (preserve_xattrs) {
		get_xattr(fname, &sx);
		cache_tmp_xattr(file, &sx);
		free_xattr(&sx);
	}
#endif

	/* Check to see if this is a device file, or link */
	if ((am_root && preserve_devices && IS_DEVICE(file->mode))
	 || (preserve_specials && IS_SPECIAL(file->mode))) {
		if (do_mknod(buf, file->mode, sx.st.st_rdev) < 0)
			rsyserr(FERROR, errno, "mknod %s failed", full_fname(buf));
		else if (DEBUG_GTE(BACKUP, 1))
			rprintf(FINFO, "make_backup: DEVICE %s successful.\n", fname);
		ret = 2;
	}

#ifdef SUPPORT_LINKS
	if (!ret && preserve_links && S_ISLNK(file->mode)) {
		const char *sl = F_SYMLINK(file);
		if (safe_symlinks && unsafe_symlink(sl, fname)) {
			if (INFO_GTE(SYMSAFE, 1)) {
				rprintf(FINFO, "not backing up unsafe symlink \"%s\" -> \"%s\"\n",
					fname, sl);
			}
			ret = 2;
		} else {
			if (do_symlink(sl, buf) < 0)
				rsyserr(FERROR, errno, "link %s -> \"%s\"", full_fname(buf), sl);
			else if (DEBUG_GTE(BACKUP, 1))
				rprintf(FINFO, "make_backup: SYMLINK %s successful.\n", fname);
			ret = 2;
		}
	}
#endif

	if (!ret && !S_ISREG(file->mode)) {
		rprintf(FINFO, "make_bak: skipping non-regular file %s\n", fname);
		unmake_file(file);
#ifdef SUPPORT_ACLS
		uncache_tmp_acls();
#endif
#ifdef SUPPORT_XATTRS
		uncache_tmp_xattrs();
#endif
		return 3;
	}

	/* Copy to backup tree if a file. */
	if (!ret) {
		if (copy_file(fname, buf, -1, file->mode) < 0) {
			rsyserr(FERROR, errno, "keep_backup failed: %s -> \"%s\"",
				full_fname(fname), buf);
			unmake_file(file);
#ifdef SUPPORT_ACLS
			uncache_tmp_acls();
#endif
#ifdef SUPPORT_XATTRS
			uncache_tmp_xattrs();
#endif
			return 0;
		}
		if (DEBUG_GTE(BACKUP, 1))
			rprintf(FINFO, "make_backup: COPY %s successful.\n", fname);
		ret = 2;
	}

	save_preserve_xattrs = preserve_xattrs;
	preserve_xattrs = 0;
	set_file_attrs(buf, file, NULL, fname, 0);
	preserve_xattrs = save_preserve_xattrs;

	unmake_file(file);
#ifdef SUPPORT_ACLS
	uncache_tmp_acls();
#endif
#ifdef SUPPORT_XATTRS
	uncache_tmp_xattrs();
#endif

  success:
	if (INFO_GTE(BACKUP, 1))
		rprintf(FINFO, "backed up %s to %s\n", fname, buf);
	return ret;
}