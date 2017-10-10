 	if (item->object.parsed)
 		return 0;
 	item->object.parsed = 1;
 	tail += size;
 	if (tail <= bufptr + tree_entry_len + 1 || memcmp(bufptr, "tree ", 5) ||
 			bufptr[tree_entry_len] != '\n')
-		return error("bogus commit object %s", sha1_to_hex(item->object.sha1));
+		return error("bogus commit object %s", oid_to_hex(&item->object.oid));
 	if (get_sha1_hex(bufptr + 5, parent.hash) < 0)
 		return error("bad tree pointer in commit %s",
-			     sha1_to_hex(item->object.sha1));
+			     oid_to_hex(&item->object.oid));
 	item->tree = lookup_tree(parent.hash);
 	bufptr += tree_entry_len + 1; /* "tree " + "hex sha1" + "\n" */
 	pptr = &item->parents;
 
-	graft = lookup_commit_graft(item->object.sha1);
+	graft = lookup_commit_graft(item->object.oid.hash);
 	while (bufptr + parent_entry_len < tail && !memcmp(bufptr, "parent ", 7)) {
 		struct commit *new_parent;
 
 		if (tail <= bufptr + parent_entry_len + 1 ||
 		    get_sha1_hex(bufptr + 7, parent.hash) ||
 		    bufptr[parent_entry_len] != '\n')
-			return error("bad parents in commit %s", sha1_to_hex(item->object.sha1));
+			return error("bad parents in commit %s", oid_to_hex(&item->object.oid));
 		bufptr += parent_entry_len + 1;
 		/*
 		 * The clone is shallow if nr_parent < 0, and we must
 		 * not traverse its real parents even when we unhide them.
 		 */
 		if (graft && (graft->nr_parent < 0 || grafts_replace_parents))
