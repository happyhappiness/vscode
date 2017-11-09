static int maybe_hard_link(struct file_struct *file, int ndx,
			   char *fname, int statret, stat_x *sxp,
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
			if (INFO_GTE(NAME, 2) && maybe_ATTRS_REPORT)
				rprintf(FCLIENT, "%s is uptodate\n", fname);
			file->flags |= FLAG_HLINK_DONE;
			return 0;
		}
	}

	if (atomic_create(file, fname, NULL, oldname, MAKEDEV(0, 0), sxp, statret == 0 ? DEL_FOR_FILE : 0)) {
		if (itemizing) {
			itemize(fname, file, ndx, statret, sxp,
				ITEM_LOCAL_CHANGE | ITEM_XNAME_FOLLOWS, 0,
				realname);
		}
		if (code != FNONE && INFO_GTE(NAME, 1))
			rprintf(code, "%s => %s\n", fname, realname);
		return 0;
	}

	return -1;
}