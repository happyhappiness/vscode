static int maybe_hard_link(struct file_struct *file, int ndx,
			   const char *fname, int statret, stat_x *sxp,
			   const char *oldname, STRUCT_STAT *old_stp,
			   const char *realname, int itemizing, enum logcode code)
{
	if (statret == 0) {
		if (sxp->st.st_dev == old_stp->st_dev
		 && sxp->st.st_ino == old_stp->st_ino) {
			if (itemizing) {
				itemize(fname, file, ndx, statret, sxp,
					ITEM_LOCAL_CHANGE | ITEM_XNAME_FOLLOWS,
					0, "");
			}
			if (verbose > 1 && maybe_ATTRS_REPORT)
				rprintf(FCLIENT, "%s is uptodate\n", fname);
			file->flags |= FLAG_HLINK_DONE;
			return 0;
		}
		if (make_backups > 0) {
			if (!make_backup(fname))
				return -1;
		} else if (robust_unlink(fname)) {
			rsyserr(FERROR_XFER, errno, "unlink %s failed",
				full_fname(fname));
			return -1;
		}
	}

	if (hard_link_one(file, fname, oldname, 0)) {
		if (itemizing) {
			itemize(fname, file, ndx, statret, sxp,
				ITEM_LOCAL_CHANGE | ITEM_XNAME_FOLLOWS, 0,
				realname);
		}
		if (code != FNONE && verbose)
			rprintf(code, "%s => %s\n", fname, realname);
		return 0;
	}
	return -1;
}