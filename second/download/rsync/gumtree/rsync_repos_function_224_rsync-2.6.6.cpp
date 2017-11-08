int hard_link_one(struct file_struct *file, int ndx, char *fname,
		  int statret, STRUCT_STAT *st, char *toname, int terse,
		  int itemizing, enum logcode code)
{
	if (do_link(toname, fname)) {
		if (terse) {
			if (!verbose)
				return -1;
			code = FINFO;
		} else
			code = FERROR;
		rsyserr(code, errno, "link %s => %s failed",
			full_fname(fname), safe_fname(toname));
		return -1;
	}

	if (itemizing) {
		itemize(file, ndx, statret, st,
			ITEM_LOCAL_CHANGE | ITEM_XNAME_FOLLOWS, 0,
			terse ? "" : toname);
	}
	if (code && verbose && !terse) {
		rprintf(code, "%s => %s\n",
			safe_fname(fname), safe_fname(toname));
	}
	return 0;
}