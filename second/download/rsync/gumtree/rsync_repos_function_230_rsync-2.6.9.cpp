static int maybe_hard_link(struct file_struct *file, int ndx,
			   char *fname, int statret, STRUCT_STAT *st,
			   char *toname, STRUCT_STAT *to_st,
			   int itemizing, enum logcode code)
{
	if (statret == 0) {
		if (st->st_dev == to_st->st_dev
		 && st->st_ino == to_st->st_ino) {
			if (itemizing) {
				itemize(file, ndx, statret, st,
					ITEM_LOCAL_CHANGE | ITEM_XNAME_FOLLOWS,
					0, "");
			}
			return 0;
		}
		if (make_backups) {
			if (!make_backup(fname))
				return -1;
		} else if (robust_unlink(fname)) {
			rsyserr(FERROR, errno, "unlink %s failed",
				full_fname(fname));
			return -1;
		}
	}
	return hard_link_one(file, ndx, fname, statret, st, toname,
			     0, itemizing, code);
}