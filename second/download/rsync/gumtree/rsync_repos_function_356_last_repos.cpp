void finish_hard_link(struct file_struct *file, const char *fname, int fin_ndx,
		      STRUCT_STAT *stp, int itemizing, enum logcode code,
		      int alt_dest)
{
	stat_x prev_sx;
	STRUCT_STAT st;
	char prev_name[MAXPATHLEN], alt_name[MAXPATHLEN];
	const char *our_name;
	struct file_list *flist;
	int prev_statret, ndx, prev_ndx = F_HL_PREV(file);

	if (stp == NULL && prev_ndx >= 0) {
		if (link_stat(fname, &st, 0) < 0 && !dry_run) {
			rsyserr(FERROR_XFER, errno, "stat %s failed",
				full_fname(fname));
			return;
		}
		stp = &st;
	}

	/* FIRST combined with DONE means we were the first to get done. */
	file->flags |= FLAG_HLINK_FIRST | FLAG_HLINK_DONE;
	F_HL_PREV(file) = alt_dest;
	if (alt_dest >= 0 && dry_run) {
		pathjoin(alt_name, MAXPATHLEN, basis_dir[alt_dest],
			 f_name(file, NULL));
		our_name = alt_name;
	} else
		our_name = fname;

	init_stat_x(&prev_sx);

	while ((ndx = prev_ndx) >= 0) {
		int val;
		flist = flist_for_ndx(ndx, "finish_hard_link");
		file = flist->files[ndx - flist->ndx_start];
		file->flags = (file->flags & ~FLAG_HLINK_FIRST) | FLAG_HLINK_DONE;
		prev_ndx = F_HL_PREV(file);
		F_HL_PREV(file) = fin_ndx;
		prev_statret = link_stat(f_name(file, prev_name), &prev_sx.st, 0);
		val = maybe_hard_link(file, ndx, prev_name, prev_statret, &prev_sx,
				      our_name, stp, fname, itemizing, code);
		flist->in_progress--;
		free_stat_x(&prev_sx);
		if (val < 0)
			continue;
		if (remove_source_files == 1 && do_xfers)
			send_msg_int(MSG_SUCCESS, ndx);
	}

	if (inc_recurse) {
		int gnum = F_HL_GNUM(file);
		struct ht_int32_node *node = hashtable_find(prior_hlinks, gnum, 0);
		if (node == NULL) {
			rprintf(FERROR, "Unable to find a hlink node for %d (%s)\n", gnum, f_name(file, prev_name));
			exit_cleanup(RERR_MESSAGEIO);
		}
		if (node->data == NULL) {
			rprintf(FERROR, "Hlink node data for %d is NULL (%s)\n", gnum, f_name(file, prev_name));
			exit_cleanup(RERR_MESSAGEIO);
		}
		if (CVAL(node->data, 0) != 0) {
			rprintf(FERROR, "Hlink node data for %d already has path=%s (%s)\n",
				gnum, (char*)node->data, f_name(file, prev_name));
			exit_cleanup(RERR_MESSAGEIO);
		}
		free(node->data);
		if (!(node->data = strdup(our_name)))
			out_of_memory("finish_hard_link");
	}
}