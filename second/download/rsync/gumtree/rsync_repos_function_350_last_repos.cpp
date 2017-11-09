static void match_gnums(int32 *ndx_list, int ndx_count)
{
	int32 from, prev;
	struct file_struct *file, *file_next;
	struct ht_int32_node *node = NULL;
	int32 gnum, gnum_next;

	qsort(ndx_list, ndx_count, sizeof ndx_list[0],
	     (int (*)()) hlink_compare_gnum);

	for (from = 0; from < ndx_count; from++) {
		file = hlink_flist->sorted[ndx_list[from]];
		gnum = F_HL_GNUM(file);
		if (inc_recurse) {
			node = hashtable_find(prior_hlinks, gnum, 1);
			if (!node->data) {
				if (!(node->data = new_array0(char, 5)))
					out_of_memory("match_gnums");
				assert(gnum >= hlink_flist->ndx_start);
				file->flags |= FLAG_HLINK_FIRST;
				prev = -1;
			} else if (CVAL(node->data, 0) == 0) {
				struct file_list *flist;
				prev = IVAL(node->data, 1);
				flist = flist_for_ndx(prev, NULL);
				if (flist)
					flist->files[prev - flist->ndx_start]->flags &= ~FLAG_HLINK_LAST;
				else {
					/* We skipped all prior files in this
					 * group, so mark this as a "first". */
					file->flags |= FLAG_HLINK_FIRST;
					prev = -1;
				}
			} else
				prev = -1;
		} else {
			file->flags |= FLAG_HLINK_FIRST;
			prev = -1;
		}
		for ( ; from < ndx_count-1; file = file_next, gnum = gnum_next, from++) { /*SHARED ITERATOR*/
			file_next = hlink_flist->sorted[ndx_list[from+1]];
			gnum_next = F_HL_GNUM(file_next);
			if (gnum != gnum_next)
				break;
			F_HL_PREV(file) = prev;
			/* The linked list uses over-the-wire ndx values. */
			if (unsort_ndx)
				prev = F_NDX(file);
			else
				prev = ndx_list[from] + hlink_flist->ndx_start;
		}
		if (prev < 0 && !inc_recurse) {
			/* Disable hard-link bit and set DONE so that
			 * HLINK_BUMP()-dependent values are unaffected. */
			file->flags &= ~(FLAG_HLINKED | FLAG_HLINK_FIRST);
			file->flags |= FLAG_HLINK_DONE;
			continue;
		}

		file->flags |= FLAG_HLINK_LAST;
		F_HL_PREV(file) = prev;
		if (inc_recurse && CVAL(node->data, 0) == 0) {
			if (unsort_ndx)
				prev = F_NDX(file);
			else
				prev = ndx_list[from] + hlink_flist->ndx_start;
			SIVAL(node->data, 1, prev);
		}
	}
}