static int delete_item(char *fname, int mode, int flags)
{
	struct file_list *dirlist;
	char buf[MAXPATHLEN];
	int j, dlen, zap_dir, ok;
	void *save_filters;

	if (!S_ISDIR(mode)) {
		if (max_delete && ++deletion_count > max_delete)
			return 0;
		if (make_backups && (backup_dir || !is_backup_file(fname)))
			ok = make_backup(fname);
		else
			ok = robust_unlink(fname) == 0;
		if (ok) {
			if (!(flags & DEL_TERSE))
				log_delete(fname, mode);
			return 0;
		}
		if (errno == ENOENT) {
			deletion_count--;
			return 0;
		}
		rsyserr(FERROR, errno, "delete_file: unlink %s failed",
			full_fname(fname));
		return -1;
	}

	zap_dir = (flags & DEL_FORCE_RECURSE || (force_delete && recurse))
		&& !(flags & DEL_NO_RECURSE);
	if ((max_delete && ++deletion_count > max_delete)
	    || (dry_run && zap_dir)) {
		ok = 0;
		errno = ENOTEMPTY;
	} else if (make_backups && !backup_dir && !is_backup_file(fname)
	    && !(flags & DEL_FORCE_RECURSE))
		ok = make_backup(fname);
	else
		ok = do_rmdir(fname) == 0;
	if (ok) {
		if (!(flags & DEL_TERSE))
			log_delete(fname, mode);
		return 0;
	}
	if (errno == ENOENT) {
		deletion_count--;
		return 0;
	}
	if (!zap_dir) {
		rsyserr(FERROR, errno, "delete_file: rmdir %s failed",
			full_fname(fname));
		return -1;
	}
	flags |= DEL_FORCE_RECURSE; /* mark subdir dels as not "in the way" */
	deletion_count--;

	dlen = strlcpy(buf, fname, MAXPATHLEN);
	save_filters = push_local_filters(buf, dlen);

	dirlist = get_dirlist(buf, dlen, 0);
	for (j = dirlist->count; j--; ) {
		struct file_struct *fp = dirlist->files[j];

		if (fp->flags & FLAG_MOUNT_POINT)
			continue;

		f_name_to(fp, buf);
		delete_item(buf, fp->mode, flags & ~DEL_TERSE);
	}
	flist_free(dirlist);

	pop_local_filters(save_filters);

	if (max_delete && ++deletion_count > max_delete)
		return 0;

	if (do_rmdir(fname) == 0) {
		if (!(flags & DEL_TERSE))
			log_delete(fname, mode);
	} else if (errno != ENOTEMPTY && errno != EEXIST && errno != ENOENT) {
		rsyserr(FERROR, errno, "delete_file: rmdir %s failed",
			full_fname(fname));
		return -1;
	}

	return 0;
}