static char *check_prior(struct file_struct *file, int gnum,
			 int *prev_ndx_p, struct file_list **flist_p)
{
	struct file_struct *fp;
	struct ht_int32_node *node;
	int prev_ndx = F_HL_PREV(file);

	while (1) {
		struct file_list *flist;
		if (prev_ndx < 0
		 || (flist = flist_for_ndx(prev_ndx, NULL)) == NULL)
			break;
		fp = flist->files[prev_ndx - flist->ndx_start];
		if (!(fp->flags & FLAG_SKIP_HLINK)) {
			*prev_ndx_p = prev_ndx;
			*flist_p = flist;
			return NULL;
		}
		F_HL_PREV(file) = prev_ndx = F_HL_PREV(fp);
	}

	if (inc_recurse
	 && (node = hashtable_find(prior_hlinks, gnum, 0)) != NULL) {
		assert(node->data != NULL);
		if (CVAL(node->data, 0) != 0) {
			*prev_ndx_p = -1;
			*flist_p = NULL;
			return node->data;
		}
		/* The prior file must have been skipped. */
		F_HL_PREV(file) = -1;
	}

	*prev_ndx_p = -1;
	*flist_p = NULL;
	return NULL;
}