 	commit_info_destroy(&ci);
 
 	return 1;
 }
 
 /*
- * The blame_entry is found to be guilty for the range.  Mark it
- * as such, and show it in incremental output.
+ * The blame_entry is found to be guilty for the range.
+ * Show it in incremental output.
  */
 static void found_guilty_entry(struct blame_entry *ent)
 {
-	if (ent->guilty)
-		return;
-	ent->guilty = 1;
 	if (incremental) {
 		struct origin *suspect = ent->suspect;
 
 		printf("%s %d %d %d\n",
 		       sha1_to_hex(suspect->commit->object.sha1),
 		       ent->s_lno + 1, ent->lno + 1, ent->num_lines);
