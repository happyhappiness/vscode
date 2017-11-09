static int try_dests_reg(struct file_struct *file, char *fname, int ndx,
			 char *cmpbuf, stat_x *sxp, int find_exact_for_existing,
			 int itemizing, enum logcode code)
{
	STRUCT_STAT real_st = sxp->st;
	int best_match = -1;
	int match_level = 0;
	int j = 0;

	do {
		pathjoin(cmpbuf, MAXPATHLEN, basis_dir[j], fname);
		if (link_stat(cmpbuf, &sxp->st, 0) < 0 || !S_ISREG(sxp->st.st_mode))
			continue;
		switch (match_level) {
		case 0:
			best_match = j;
			match_level = 1;
			/* FALL THROUGH */
		case 1:
			if (!unchanged_file(cmpbuf, file, &sxp->st))
				continue;
			best_match = j;
			match_level = 2;
			/* FALL THROUGH */
		case 2:
			if (!unchanged_attrs(cmpbuf, file, sxp)) {
				free_stat_x(sxp);
				continue;
			}
			best_match = j;
			match_level = 3;
			break;
		}
		break;
	} while (basis_dir[++j] != NULL);

	if (!match_level)
		goto got_nothing_for_ya;

	if (j != best_match) {
		j = best_match;
		pathjoin(cmpbuf, MAXPATHLEN, basis_dir[j], fname);
		if (link_stat(cmpbuf, &sxp->st, 0) < 0)
			goto got_nothing_for_ya;
	}

	if (match_level == 3 && !copy_dest) {
		if (find_exact_for_existing) {
			if (link_dest && real_st.st_dev == sxp->st.st_dev && real_st.st_ino == sxp->st.st_ino)
				return -1;
			if (do_unlink(fname) < 0 && errno != ENOENT)
				goto got_nothing_for_ya;
		}
#ifdef SUPPORT_HARD_LINKS
		if (link_dest) {
			if (!hard_link_one(file, fname, cmpbuf, 1))
				goto try_a_copy;
			if (preserve_hard_links && F_IS_HLINKED(file))
				finish_hard_link(file, fname, ndx, &sxp->st, itemizing, code, j);
			if (!maybe_ATTRS_REPORT && (INFO_GTE(NAME, 2) || stdout_format_has_i > 1)) {
				itemize(cmpbuf, file, ndx, 1, sxp,
					ITEM_LOCAL_CHANGE | ITEM_XNAME_FOLLOWS,
					0, "");
			}
		} else
#endif
		{
			if (itemizing)
				itemize(cmpbuf, file, ndx, 0, sxp, 0, 0, NULL);
		}
		if (INFO_GTE(NAME, 2) && maybe_ATTRS_REPORT)
			rprintf(FCLIENT, "%s is uptodate\n", fname);
		return -2;
	}

	if (find_exact_for_existing)
		goto got_nothing_for_ya;

	if (match_level >= 2) {
#ifdef SUPPORT_HARD_LINKS
	  try_a_copy: /* Copy the file locally. */
#endif
		if (!dry_run && copy_altdest_file(cmpbuf, fname, file) < 0) {
			if (find_exact_for_existing) /* Can get here via hard-link failure */
				goto got_nothing_for_ya;
			return -1;
		}
		if (itemizing)
			itemize(cmpbuf, file, ndx, 0, sxp, ITEM_LOCAL_CHANGE, 0, NULL);
		if (maybe_ATTRS_REPORT
		 && ((!itemizing && INFO_GTE(NAME, 1) && match_level == 2)
		  || (INFO_GTE(NAME, 2) && match_level == 3))) {
			code = match_level == 3 ? FCLIENT : FINFO;
			rprintf(code, "%s%s\n", fname,
				match_level == 3 ? " is uptodate" : "");
		}
#ifdef SUPPORT_HARD_LINKS
		if (preserve_hard_links && F_IS_HLINKED(file))
			finish_hard_link(file, fname, ndx, &sxp->st, itemizing, code, -1);
#endif
		return -2;
	}

	return FNAMECMP_BASIS_DIR_LOW + j;

got_nothing_for_ya:
	sxp->st = real_st;
	return -1;
}