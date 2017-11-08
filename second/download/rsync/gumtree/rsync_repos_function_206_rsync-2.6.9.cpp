static int try_dests_non(struct file_struct *file, char *fname, int ndx,
			 int itemizing, int maybe_ATTRS_REPORT,
			 enum logcode code)
{
	char fnamebuf[MAXPATHLEN];
	STRUCT_STAT st;
	int i = 0;

	do {
		pathjoin(fnamebuf, MAXPATHLEN, basis_dir[i], fname);
		if (link_stat(fnamebuf, &st, 0) < 0 || S_ISDIR(st.st_mode)
		 || !unchanged_attrs(file, &st))
			continue;
		if (S_ISLNK(file->mode)) {
#ifdef SUPPORT_LINKS
			char lnk[MAXPATHLEN];
			int len;
			if ((len = readlink(fnamebuf, lnk, MAXPATHLEN-1)) <= 0)
				continue;
			lnk[len] = '\0';
			if (strcmp(lnk, file->u.link) != 0)
#endif
				continue;
		} else if (IS_SPECIAL(file->mode)) {
			if (!IS_SPECIAL(st.st_mode) || st.st_rdev != file->u.rdev)
				continue;
		} else if (IS_DEVICE(file->mode)) {
			if (!IS_DEVICE(st.st_mode) || st.st_rdev != file->u.rdev)
				continue;
		} else {
			rprintf(FERROR,
				"internal: try_dests_non() called with invalid mode (%o)\n",
				(int)file->mode);
			exit_cleanup(RERR_UNSUPPORTED);
		}
#ifdef SUPPORT_HARD_LINKS
		if (link_dest
#ifndef CAN_HARDLINK_SYMLINK
		 && !S_ISLNK(file->mode)
#endif
#ifndef CAN_HARDLINK_SPECIAL
		 && !IS_SPECIAL(file->mode) && !IS_DEVICE(file->mode)
#endif
		) {
			if (do_link(fnamebuf, fname) < 0) {
				rsyserr(FERROR, errno,
					"failed to hard-link %s with %s",
					fnamebuf, fname);
				break;
			}
			if (preserve_hard_links && file->link_u.links)
				hard_link_cluster(file, ndx, itemizing, code);
		}
#endif
		if (itemizing && stdout_format_has_i && verbose > 1) {
			int changes = compare_dest ? 0 : ITEM_LOCAL_CHANGE
				    + (link_dest ? ITEM_XNAME_FOLLOWS : 0);
			char *lp = link_dest ? "" : NULL;
			itemize(file, ndx, 0, &st, changes, 0, lp);
		}
		if (verbose > 1 && maybe_ATTRS_REPORT) {
			rprintf(FCLIENT, "%s is uptodate\n", fname);
		}
		return -2;
	} while (basis_dir[++i] != NULL);

	return -1;
}