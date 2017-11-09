static BOOL copy_valid_path(const char *fname)
{
	const char *f;
	int val;
	BOOL ret = True;
	stat_x sx;
	char *b, *rel = backup_dir_buf + backup_dir_len, *name = rel;

	for (f = fname, b = rel; *f && *f == *b; f++, b++) {
		if (*b == '/')
			name = b + 1;
	}

	if (stringjoin(rel, backup_dir_remainder, fname, backup_suffix, NULL) >= backup_dir_remainder) {
		rprintf(FERROR, "backup filename too long\n");
		*name = '\0';
		return False;
	}

	for ( ; ; name = b + 1) {
		if ((b = strchr(name, '/')) == NULL)
			return True;
		*b = '\0';

		val = validate_backup_dir();
		if (val == 0)
			break;
		if (val < 0) {
			*name = '\0';
			return False;
		}

		*b = '/';
	}

	init_stat_x(&sx);

	for ( ; b; name = b + 1, b = strchr(name, '/')) {
		*b = '\0';

		while (do_mkdir(backup_dir_buf, ACCESSPERMS) < 0) {
			if (errno == EEXIST) {
				val = validate_backup_dir();
				if (val > 0)
					break;
				if (val == 0)
					continue;
			} else
				rsyserr(FERROR, errno, "backup mkdir %s failed", backup_dir_buf);
			*name = '\0';
			ret = False;
			goto cleanup;
		}

		/* Try to transfer the directory settings of the actual dir
		 * that the files are coming from. */
		if (x_stat(rel, &sx.st, NULL) < 0)
			rsyserr(FERROR, errno, "backup stat %s failed", full_fname(rel));
		else {
			struct file_struct *file;
			if (!(file = make_file(rel, NULL, NULL, 0, NO_FILTERS)))
				continue;
#ifdef SUPPORT_ACLS
			if (preserve_acls && !S_ISLNK(file->mode)) {
				get_acl(rel, &sx);
				cache_tmp_acl(file, &sx);
				free_acl(&sx);
			}
#endif
#ifdef SUPPORT_XATTRS
			if (preserve_xattrs) {
				get_xattr(rel, &sx);
				cache_tmp_xattr(file, &sx);
				free_xattr(&sx);
			}
#endif
			set_file_attrs(backup_dir_buf, file, NULL, NULL, 0);
			unmake_file(file);
		}

		*b = '/';
	}

  cleanup:

#ifdef SUPPORT_ACLS
	uncache_tmp_acls();
#endif
#ifdef SUPPORT_XATTRS
	uncache_tmp_xattrs();
#endif

	return ret;
}