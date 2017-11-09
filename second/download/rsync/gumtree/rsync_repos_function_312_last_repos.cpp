static int try_dests_non(struct file_struct *file, char *fname, int ndx,
			 char *cmpbuf, stat_x *sxp, int itemizing,
			 enum logcode code)
{
	int best_match = -1;
	int match_level = 0;
	enum nonregtype type;
	uint32 *devp;
#ifdef SUPPORT_LINKS
	char lnk[MAXPATHLEN];
	int len;
#endif
	int j = 0;

#ifndef SUPPORT_LINKS
	if (S_ISLNK(file->mode))
		return -1;
#endif
	if (S_ISDIR(file->mode)) {
		type = TYPE_DIR;
	} else if (IS_SPECIAL(file->mode))
		type = TYPE_SPECIAL;
	else if (IS_DEVICE(file->mode))
		type = TYPE_DEVICE;
#ifdef SUPPORT_LINKS
	else if (S_ISLNK(file->mode))
		type = TYPE_SYMLINK;
#endif
	else {
		rprintf(FERROR,
			"internal: try_dests_non() called with invalid mode (%o)\n",
			(int)file->mode);
		exit_cleanup(RERR_UNSUPPORTED);
	}

	do {
		pathjoin(cmpbuf, MAXPATHLEN, basis_dir[j], fname);
		if (link_stat(cmpbuf, &sxp->st, 0) < 0)
			continue;
		switch (type) {
		case TYPE_DIR:
			if (!S_ISDIR(sxp->st.st_mode))
				continue;
			break;
		case TYPE_SPECIAL:
			if (!IS_SPECIAL(sxp->st.st_mode))
				continue;
			break;
		case TYPE_DEVICE:
			if (!IS_DEVICE(sxp->st.st_mode))
				continue;
			break;
		case TYPE_SYMLINK:
#ifdef SUPPORT_LINKS
			if (!S_ISLNK(sxp->st.st_mode))
				continue;
			break;
#else
			return -1;
#endif
		}
		if (match_level < 1) {
			match_level = 1;
			best_match = j;
		}
		switch (type) {
		case TYPE_DIR:
		case TYPE_SPECIAL:
			break;
		case TYPE_DEVICE:
			devp = F_RDEV_P(file);
			if (sxp->st.st_rdev != MAKEDEV(DEV_MAJOR(devp), DEV_MINOR(devp)))
				continue;
			break;
		case TYPE_SYMLINK:
#ifdef SUPPORT_LINKS
			if ((len = do_readlink(cmpbuf, lnk, MAXPATHLEN-1)) <= 0)
				continue;
			lnk[len] = '\0';
			if (strcmp(lnk, F_SYMLINK(file)) != 0)
				continue;
			break;
#else
			return -1;
#endif
		}
		if (match_level < 2) {
			match_level = 2;
			best_match = j;
		}
		if (unchanged_attrs(cmpbuf, file, sxp)) {
			match_level = 3;
			best_match = j;
			break;
		}
	} while (basis_dir[++j] != NULL);

	if (!match_level)
		return -1;

	if (j != best_match) {
		j = best_match;
		pathjoin(cmpbuf, MAXPATHLEN, basis_dir[j], fname);
		if (link_stat(cmpbuf, &sxp->st, 0) < 0)
			return -1;
	}

	if (match_level == 3) {
#ifdef SUPPORT_HARD_LINKS
		if (link_dest
#ifndef CAN_HARDLINK_SYMLINK
		 && !S_ISLNK(file->mode)
#endif
#ifndef CAN_HARDLINK_SPECIAL
		 && !IS_SPECIAL(file->mode) && !IS_DEVICE(file->mode)
#endif
		 && !S_ISDIR(file->mode)) {
			if (do_link(cmpbuf, fname) < 0) {
				rsyserr(FERROR_XFER, errno,
					"failed to hard-link %s with %s",
					cmpbuf, fname);
				return j;
			}
			if (preserve_hard_links && F_IS_HLINKED(file))
				finish_hard_link(file, fname, ndx, NULL, itemizing, code, -1);
		} else
#endif
			match_level = 2;
		if (itemizing && stdout_format_has_i
		 && (INFO_GTE(NAME, 2) || stdout_format_has_i > 1)) {
			int chg = compare_dest && type != TYPE_DIR ? 0
			    : ITEM_LOCAL_CHANGE + (match_level == 3 ? ITEM_XNAME_FOLLOWS : 0);
			char *lp = match_level == 3 ? "" : NULL;
			itemize(cmpbuf, file, ndx, 0, sxp, chg + ITEM_MATCHED, 0, lp);
		}
		if (INFO_GTE(NAME, 2) && maybe_ATTRS_REPORT) {
			rprintf(FCLIENT, "%s%s is uptodate\n",
				fname, type == TYPE_DIR ? "/" : "");
		}
		return -2;
	}

	return j;
}