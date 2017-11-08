static int try_dests_reg(struct file_struct *file, char *fname, int ndx,
			 char *cmpbuf, STRUCT_STAT *stp, int itemizing,
			 int maybe_ATTRS_REPORT, enum logcode code)
{
	int best_match = -1;
	int match_level = 0;
	int j = 0;

	do {
		pathjoin(cmpbuf, MAXPATHLEN, basis_dir[j], fname);
		if (link_stat(cmpbuf, stp, 0) < 0 || !S_ISREG(stp->st_mode))
			continue;
		switch (match_level) {
		case 0:
			best_match = j;
			match_level = 1;
			/* FALL THROUGH */
		case 1:
			if (!unchanged_file(cmpbuf, file, stp))
				continue;
			best_match = j;
			match_level = 2;
			/* FALL THROUGH */
		case 2:
			if (!unchanged_attrs(file, stp))
				continue;
			if (always_checksum && preserve_times
			 && cmp_time(stp->st_mtime, file->modtime))
				continue;
			best_match = j;
			match_level = 3;
			break;
		}
		break;
	} while (basis_dir[++j] != NULL);

	if (!match_level)
		return -1;

	if (j != best_match) {
		j = best_match;
		pathjoin(cmpbuf, MAXPATHLEN, basis_dir[j], fname);
		if (link_stat(cmpbuf, stp, 0) < 0)
			return -1;
	}

	if (match_level == 3 && !copy_dest) {
#ifdef SUPPORT_HARD_LINKS
		if (link_dest) {
			if (hard_link_one(file, ndx, fname, 0, stp,
					  cmpbuf, 1,
					  itemizing && verbose > 1,
					  code) < 0)
				goto try_a_copy;
			if (preserve_hard_links && file->link_u.links) {
				if (dry_run)
					file->link_u.links->link_dest_used = j + 1;
				hard_link_cluster(file, ndx, itemizing, code);
			}
		} else
#endif
		if (itemizing)
			itemize(file, ndx, 0, stp, 0, 0, NULL);
		if (verbose > 1 && maybe_ATTRS_REPORT) {
			rprintf(FCLIENT, "%s is uptodate\n", fname);
		}
		return -2;
	}

	if (match_level >= 2) {
	  try_a_copy: /* Copy the file locally. */
		if (copy_file(cmpbuf, fname, file->mode) < 0) {
			if (verbose) {
				rsyserr(FINFO, errno, "copy_file %s => %s",
					full_fname(cmpbuf), fname);
			}
			return -1;
		}
		if (itemizing)
			itemize(file, ndx, 0, stp, ITEM_LOCAL_CHANGE, 0, NULL);
		set_file_attrs(fname, file, NULL, 0);
		if (maybe_ATTRS_REPORT
		 && ((!itemizing && verbose && match_level == 2)
		  || (verbose > 1 && match_level == 3))) {
			code = match_level == 3 ? FCLIENT : FINFO;
			rprintf(code, "%s%s\n", fname,
				match_level == 3 ? " is uptodate" : "");
		}
		if (preserve_hard_links && file->link_u.links)
			hard_link_cluster(file, ndx, itemizing, code);
		return -2;
	}

	return FNAMECMP_BASIS_DIR_LOW + j;
}