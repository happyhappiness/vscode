static char *get_local_name(struct file_list *flist, char *dest_path)
{
	STRUCT_STAT st;
	int statret;
	char *cp;

	if (DEBUG_GTE(RECV, 1)) {
		rprintf(FINFO, "get_local_name count=%d %s\n",
			file_total, NS(dest_path));
	}

	if (!dest_path || list_only)
		return NULL;

	/* Treat an empty string as a copy into the current directory. */
	if (!*dest_path)
	    dest_path = ".";

	if (daemon_filter_list.head) {
		char *slash = strrchr(dest_path, '/');
		if (slash && (slash[1] == '\0' || (slash[1] == '.' && slash[2] == '\0')))
			*slash = '\0';
		else
			slash = NULL;
		if ((*dest_path != '.' || dest_path[1] != '\0')
		 && (check_filter(&daemon_filter_list, FLOG, dest_path, 0) < 0
		  || check_filter(&daemon_filter_list, FLOG, dest_path, 1) < 0)) {
			rprintf(FERROR, "ERROR: daemon has excluded destination \"%s\"\n",
				dest_path);
			exit_cleanup(RERR_FILESELECT);
		}
		if (slash)
			*slash = '/';
	}

	/* See what currently exists at the destination. */
	if ((statret = do_stat(dest_path, &st)) == 0) {
		/* If the destination is a dir, enter it and use mode 1. */
		if (S_ISDIR(st.st_mode)) {
			if (!change_dir(dest_path, CD_NORMAL)) {
				rsyserr(FERROR, errno, "change_dir#1 %s failed",
					full_fname(dest_path));
				exit_cleanup(RERR_FILESELECT);
			}
			filesystem_dev = st.st_dev; /* ensures --force works right w/-x */
			return NULL;
		}
		if (file_total > 1) {
			rprintf(FERROR,
				"ERROR: destination must be a directory when"
				" copying more than 1 file\n");
			exit_cleanup(RERR_FILESELECT);
		}
		if (file_total == 1 && S_ISDIR(flist->files[0]->mode)) {
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
	if (file_total > 1 || (cp && !cp[1])) {
		/* Lop off the final slash (if any). */
		if (cp && !cp[1])
			*cp = '\0';

		if (statret == 0) {
			rprintf(FERROR,
			    "ERROR: destination path is not a directory\n");
			exit_cleanup(RERR_SYNTAX);
		}

		if (do_mkdir(dest_path, ACCESSPERMS) != 0) {
			rsyserr(FERROR, errno, "mkdir %s failed",
				full_fname(dest_path));
			exit_cleanup(RERR_FILEIO);
		}

		if (flist->high >= flist->low
		 && strcmp(flist->files[flist->low]->basename, ".") == 0)
			flist->files[0]->flags |= FLAG_DIR_CREATED;

		if (INFO_GTE(NAME, 1))
			rprintf(FINFO, "created directory %s\n", dest_path);

		if (dry_run) {
			/* Indicate that dest dir doesn't really exist. */
			dry_run++;
		}

		if (!change_dir(dest_path, dry_run > 1 ? CD_SKIP_CHDIR : CD_NORMAL)) {
			rsyserr(FERROR, errno, "change_dir#2 %s failed",
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
	if (!change_dir(dest_path, CD_NORMAL)) {
		rsyserr(FERROR, errno, "change_dir#3 %s failed",
			full_fname(dest_path));
		exit_cleanup(RERR_FILESELECT);
	}
	*cp = '/';

	return cp + 1;
}