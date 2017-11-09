static inline int link_or_rename(const char *from, const char *to,
				 BOOL prefer_rename, STRUCT_STAT *stp)
{
#ifdef SUPPORT_HARD_LINKS
	if (!prefer_rename) {
#ifndef CAN_HARDLINK_SYMLINK
		if (S_ISLNK(stp->st_mode))
			return 0; /* Use copy code. */
#endif
#ifndef CAN_HARDLINK_SPECIAL
		if (IS_SPECIAL(stp->st_mode) || IS_DEVICE(stp->st_mode))
			return 0; /* Use copy code. */
#endif
		if (do_link(from, to) == 0) {
			if (DEBUG_GTE(BACKUP, 1))
				rprintf(FINFO, "make_backup: HLINK %s successful.\n", from);
			return 2;
		}
		/* We prefer to rename a regular file rather than copy it. */
		if (!S_ISREG(stp->st_mode) || errno == EEXIST || errno == EISDIR)
			return 0;
	}
#endif
	if (do_rename(from, to) == 0) {
		if (stp->st_nlink > 1 && !S_ISDIR(stp->st_mode)) {
			/* If someone has hard-linked the file into the backup
			 * dir, rename() might return success but do nothing! */
			robust_unlink(from); /* Just in case... */
		}
		if (DEBUG_GTE(BACKUP, 1))
			rprintf(FINFO, "make_backup: RENAME %s successful.\n", from);
		return 1;
	}
	return 0;
}