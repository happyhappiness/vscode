 	for (from = 0; from < ndx_count; from++) {
 		file = hlink_flist->sorted[ndx_list[from]];
 		gnum = F_HL_GNUM(file);
 		if (inc_recurse) {
 			node = hashtable_find(prior_hlinks, gnum, 1);
 			if (!node->data) {
-				node->data = new_array0(char, 5);
+				if (!(node->data = new_array0(char, 5)))
+					out_of_memory("match_gnums");
 				assert(gnum >= hlink_flist->ndx_start);
 				file->flags |= FLAG_HLINK_FIRST;
 				prev = -1;
 			} else if (CVAL(node->data, 0) == 0) {
 				struct file_list *flist;
 				prev = IVAL(node->data, 1);
-				flist = flist_for_ndx(prev);
+				flist = flist_for_ndx(prev, NULL);
 				if (flist)
 					flist->files[prev - flist->ndx_start]->flags &= ~FLAG_HLINK_LAST;
 				else {
 					/* We skipped all prior files in this
 					 * group, so mark this as a "first". */
 					file->flags |= FLAG_HLINK_FIRST;
