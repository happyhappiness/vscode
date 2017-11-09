static enum delret delete_dir_contents(char *fname, uint16 flags)
{
	struct file_list *dirlist;
	enum delret ret;
	unsigned remainder;
	void *save_filters;
	int j, dlen;
	char *p;

	if (DEBUG_GTE(DEL, 3)) {
		rprintf(FINFO, "delete_dir_contents(%s) flags=%d\n",
			fname, flags);
	}

	dlen = strlen(fname);
	save_filters = push_local_filters(fname, dlen);

	non_perishable_cnt = 0;
	dirlist = get_dirlist(fname, dlen, 0);
	ret = non_perishable_cnt ? DR_NOT_EMPTY : DR_SUCCESS;

	if (!dirlist->used)
		goto done;

	if (!(flags & DEL_RECURSE)) {
		ret = DR_NOT_EMPTY;
		goto done;
	}

	p = fname + dlen;
	if (dlen != 1 || *fname != '/')
		*p++ = '/';
	remainder = MAXPATHLEN - (p - fname);

	/* We do our own recursion, so make delete_item() non-recursive. */
	flags = (flags & ~(DEL_RECURSE|DEL_MAKE_ROOM|DEL_NO_UID_WRITE))
	      | DEL_DIR_IS_EMPTY;

	for (j = dirlist->used; j--; ) {
		struct file_struct *fp = dirlist->files[j];

		if (fp->flags & FLAG_MOUNT_DIR && S_ISDIR(fp->mode)) {
			if (DEBUG_GTE(DEL, 1)) {
				rprintf(FINFO,
				    "mount point, %s, pins parent directory\n",
				    f_name(fp, NULL));
			}
			ret = DR_NOT_EMPTY;
			continue;
		}

		strlcpy(p, fp->basename, remainder);
		if (!(fp->mode & S_IWUSR) && !am_root && fp->flags & FLAG_OWNED_BY_US)
			do_chmod(fname, fp->mode | S_IWUSR);
		/* Save stack by recursing to ourself directly. */
		if (S_ISDIR(fp->mode)) {
			if (delete_dir_contents(fname, flags | DEL_RECURSE) != DR_SUCCESS)
				ret = DR_NOT_EMPTY;
		}
		if (delete_item(fname, fp->mode, flags) != DR_SUCCESS)
			ret = DR_NOT_EMPTY;
	}

	fname[dlen] = '\0';

  done:
	flist_free(dirlist);
	pop_local_filters(save_filters);

	if (ret == DR_NOT_EMPTY) {
		rprintf(FINFO, "cannot delete non-empty directory: %s\n",
			fname);
	}
	return ret;
}