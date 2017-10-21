 /* Analyze the hard-links in the file-list by creating a list of all the
  * items that have hlink data, sorting them, and matching up identical
  * values into clusters.  These will be a single linked list from last
  * to first when we're done. */
 void match_hard_links(struct file_list *flist)
 {
-	if (!list_only) {
+	if (!list_only && flist->used) {
 		int i, ndx_count = 0;
 		int32 *ndx_list;
 
 		if (!(ndx_list = new_array(int32, flist->used)))
 			out_of_memory("match_hard_links");
 
