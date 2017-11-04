void finish_hard_link(struct file_struct *file, const char *fname, int fin_ndx,
		      STRUCT_STAT *stp, int itemizing, enum logcode code,
		      int alt_dest)
{
	stat_x prev_sx;
	STRUCT_STAT st;
	char alt_name[MAXPATHLEN], *prev_name;
	const char *our_name;
	struct file_list *flist;
	int prev_statret, ndx, prev_ndx = F_HL_PREV(file);

	if (stp == NULL && prev_ndx >= 0) {
		if (link_stat(fname, &st, 0) < 0) {
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

#ifdef SUPPORT_ACLS
	prev_sx.acc_acl = prev_sx.def_acl = NULL;
#endif

	while ((ndx = prev_ndx) >= 0) {
		int val;
		flist = flist_for_ndx(ndx);
		assert(flist != NULL);
		file = flist->files[ndx - flist->ndx_start];
		file->flags = (file->flags & ~FLAG_HLINK_FIRST) | FLAG_HLINK_DONE;
		prev_ndx = F_HL_PREV(file);
		F_HL_PREV(file) = fin_ndx;
		prev_name = f_name(file, NULL);
		prev_statret = link_stat(prev_name, &prev_sx.st, 0);
		val = maybe_hard_link(file, ndx, prev_name, prev_statret, &prev_sx,
				      our_name, stp, fname, itemizing, code);
		flist->in_progress--;
#ifdef SUPPORT_ACLS
		if (preserve_acls)
			free_acl(&prev_sx);
#endif
		if (val < 0)
			continue;
		if (remove_source_files == 1 && do_xfers)
			send_msg_int(MSG_SUCCESS, ndx);
	}

	if (inc_recurse) {
		int gnum = F_HL_GNUM(file);
		struct ht_int32_node *node = hashtable_find(prior_hlinks, gnum, 0);
		assert(node != NULL && node->data != NULL);
		assert(CVAL(node->data, 0) == 0);
		free(node->data);
		if (!(node->data = strdup(our_name)))
			out_of_memory("finish_hard_link");
	}
}