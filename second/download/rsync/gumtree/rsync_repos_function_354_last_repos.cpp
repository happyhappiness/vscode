int hard_link_check(struct file_struct *file, int ndx, char *fname,
		    int statret, stat_x *sxp, int itemizing,
		    enum logcode code)
{
	STRUCT_STAT prev_st;
	char namebuf[MAXPATHLEN], altbuf[MAXPATHLEN];
	char *realname, *prev_name;
	struct file_list *flist;
	int gnum = inc_recurse ? F_HL_GNUM(file) : -1;
	int prev_ndx;

	prev_name = realname = check_prior(file, gnum, &prev_ndx, &flist);

	if (!prev_name) {
		struct file_struct *prev_file;

		if (!flist) {
			/* The previous file was skipped, so this one is
			 * treated as if it were the first in its group. */
			if (DEBUG_GTE(HLINK, 2)) {
				rprintf(FINFO, "hlink for %d (%s,%d): virtual first\n",
					ndx, f_name(file, NULL), gnum);
			}
			return 0;
		}

		prev_file = flist->files[prev_ndx - flist->ndx_start];

		/* Is the previous link not complete yet? */
		if (!(prev_file->flags & FLAG_HLINK_DONE)) {
			/* Is the previous link being transferred? */
			if (prev_file->flags & FLAG_FILE_SENT) {
				/* Add ourselves to the list of files that will
				 * be updated when the transfer completes, and
				 * mark ourself as waiting for the transfer. */
				F_HL_PREV(file) = F_HL_PREV(prev_file);
				F_HL_PREV(prev_file) = ndx;
				file->flags |= FLAG_FILE_SENT;
				cur_flist->in_progress++;
				if (DEBUG_GTE(HLINK, 2)) {
					rprintf(FINFO, "hlink for %d (%s,%d): waiting for %d\n",
						ndx, f_name(file, NULL), gnum, F_HL_PREV(file));
				}
				return 1;
			}
			if (DEBUG_GTE(HLINK, 2)) {
				rprintf(FINFO, "hlink for %d (%s,%d): looking for a leader\n",
					ndx, f_name(file, NULL), gnum);
			}
			return 0;
		}

		/* There is a finished file to link with! */
		if (!(prev_file->flags & FLAG_HLINK_FIRST)) {
			/* The previous previous is FIRST when prev is not. */
			prev_name = realname = check_prior(prev_file, gnum, &prev_ndx, &flist);
			/* Update our previous pointer to point to the FIRST. */
			F_HL_PREV(file) = prev_ndx;
		}

		if (!prev_name) {
			int alt_dest;

			assert(flist != NULL);
			prev_file = flist->files[prev_ndx - flist->ndx_start];
			/* F_HL_PREV() is alt_dest value when DONE && FIRST. */
			alt_dest = F_HL_PREV(prev_file);
			if (DEBUG_GTE(HLINK, 2)) {
				rprintf(FINFO, "hlink for %d (%s,%d): found flist match (alt %d)\n",
					ndx, f_name(file, NULL), gnum, alt_dest);
			}

			if (alt_dest >= 0 && dry_run) {
				pathjoin(namebuf, MAXPATHLEN, basis_dir[alt_dest],
					 f_name(prev_file, NULL));
				prev_name = namebuf;
				realname = f_name(prev_file, altbuf);
			} else {
				prev_name = f_name(prev_file, namebuf);
				realname = prev_name;
			}
		}
	}

	if (DEBUG_GTE(HLINK, 2)) {
		rprintf(FINFO, "hlink for %d (%s,%d): leader is %d (%s)\n",
			ndx, f_name(file, NULL), gnum, prev_ndx, prev_name);
	}

	if (link_stat(prev_name, &prev_st, 0) < 0) {
		if (!dry_run || errno != ENOENT) {
			rsyserr(FERROR_XFER, errno, "stat %s failed", full_fname(prev_name));
			return -1;
		}
		/* A new hard-link will get a new dev & inode, so approximate
		 * those values in dry-run mode by zeroing them. */
		memset(&prev_st, 0, sizeof prev_st);
	}

	if (statret < 0 && basis_dir[0] != NULL) {
		/* If we match an alt-dest item, we don't output this as a change. */
		char cmpbuf[MAXPATHLEN];
		stat_x alt_sx;
		int j = 0;
		init_stat_x(&alt_sx);
		do {
			pathjoin(cmpbuf, MAXPATHLEN, basis_dir[j], fname);
			if (link_stat(cmpbuf, &alt_sx.st, 0) < 0)
				continue;
			if (link_dest) {
				if (prev_st.st_dev != alt_sx.st.st_dev
				 || prev_st.st_ino != alt_sx.st.st_ino)
					continue;
				statret = 1;
				if (stdout_format_has_i == 0
				 || (!INFO_GTE(NAME, 2) && stdout_format_has_i < 2)) {
					itemizing = 0;
					code = FNONE;
					if (INFO_GTE(NAME, 2) && maybe_ATTRS_REPORT)
						rprintf(FCLIENT, "%s is uptodate\n", fname);
				}
				break;
			}
			if (!unchanged_file(cmpbuf, file, &alt_sx.st))
				continue;
			statret = 1;
			if (unchanged_attrs(cmpbuf, file, &alt_sx))
				break;
		} while (basis_dir[++j] != NULL);
		if (statret == 1) {
			sxp->st = alt_sx.st;
#ifdef SUPPORT_ACLS
			if (preserve_acls && !S_ISLNK(file->mode)) {
				free_acl(sxp);
				if (!ACL_READY(alt_sx))
					get_acl(cmpbuf, sxp);
				else {
					sxp->acc_acl = alt_sx.acc_acl;
					sxp->def_acl = alt_sx.def_acl;
					alt_sx.acc_acl = alt_sx.def_acl = NULL;
				}
			}
#endif
#ifdef SUPPORT_XATTRS
			if (preserve_xattrs) {
				free_xattr(sxp);
				if (!XATTR_READY(alt_sx))
					get_xattr(cmpbuf, sxp);
				else {
					sxp->xattr = alt_sx.xattr;
					alt_sx.xattr = NULL;
				}
			}
#endif
		} else
			free_stat_x(&alt_sx);
	}

	if (maybe_hard_link(file, ndx, fname, statret, sxp, prev_name, &prev_st,
			    realname, itemizing, code) < 0)
		return -1;

	if (remove_source_files == 1 && do_xfers)
		send_msg_int(MSG_SUCCESS, ndx);

	return 1;
}