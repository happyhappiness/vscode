static char *get_local_name(struct file_list *flist, char *dest_path)
{
	STRUCT_STAT st;
	int statret;
	char *cp;

	if (verbose > 2) {
		rprintf(FINFO, "get_local_name count=%d %s\n",
			flist->count, NS(dest_path));
	}

	if (!dest_path || list_only)
		return NULL;

	/* See what currently exists at the destination. */
	if ((statret = do_stat(dest_path, &st)) == 0) {
		/* If the destination is a dir, enter it and use mode 1. */
		if (S_ISDIR(st.st_mode)) {
			if (!push_dir(dest_path, 0)) {
				rsyserr(FERROR, errno, "push_dir#1 %s failed",
					full_fname(dest_path));
				exit_cleanup(RERR_FILESELECT);
			}
			return NULL;
		}
		if (flist->count > 1) {
			rprintf(FERROR,
				"ERROR: destination must be a directory when"
				" copying more than 1 file\n");
			exit_cleanup(RERR_FILESELECT);
		}
		/* Caution: flist->count could be 0! */
		if (flist->count == 1 && S_ISDIR(flist->files[0]->mode)) {
			rprintf(FERROR,
				"ERROR: cannot overwrite non-directory"
				" with a directory\n");
			exit_cleanup(RERR_FILESELECT);
		}
	} else if (errno != ENOENT) {
		/* If we don't know what's at the destination, fail. */
		rsyserr(FERROR, errno, "ERROR: cannot stat destination %s",
			full_fname(dest_path));
		exit_cleanup(RERR_FILESELECT);
	}

	cp = strrchr(dest_path, '/');

	/* If we need a destination directory because the transfer is not
	 * of a single non-directory or the user has requested one via a
	 * destination path ending in a slash, create one and use mode 1. */
	if (flist->count > 1 || (cp && !cp[1])) {
		/* Lop off the final slash (if any). */
		if (cp && !cp[1])
			*cp = '\0';

		if (statret == 0) {
			rprintf(FERROR,
			    "ERROR: destination path is not a directory\n");
			exit_cleanup(RERR_SYNTAX);
		}

		if (mkdir_defmode(dest_path) != 0) {
			rsyserr(FERROR, errno, "mkdir %s failed",
				full_fname(dest_path));
			exit_cleanup(RERR_FILEIO);
		}

		new_root_dir = 1;

		if (verbose)
			rprintf(FINFO, "created directory %s\n", dest_path);

		if (dry_run) {
			/* Indicate that dest dir doesn't really exist. */
			dry_run++;
		}

		if (!push_dir(dest_path, dry_run > 1)) {
			rsyserr(FERROR, errno, "push_dir#2 %s failed",
				full_fname(dest_path));
			exit_cleanup(RERR_FILESELECT);
		}

		return NULL;
	}

	/* Otherwise, we are writing a single file, possibly on top of an
	 * existing non-directory.  Change to the item's parent directory
	 * (if it has a path component), return the basename of the
	 * destination file as the local name, and use mode 2. */
	if (!cp)
		return dest_path;

	if (cp == dest_path)
		dest_path = "/";

	*cp = '\0';
	if (!push_dir(dest_path, 0)) {
		rsyserr(FERROR, errno, "push_dir#3 %s failed",
			full_fname(dest_path));
		exit_cleanup(RERR_FILESELECT);
	}
	*cp = '/';

	return cp + 1;
}