 	if (tail <= bufptr + tree_entry_len + 1 || memcmp(bufptr, "tree ", 5) ||
 			bufptr[tree_entry_len] != '\n')
 		return error("bogus commit object %s", oid_to_hex(&item->object.oid));
 	if (get_sha1_hex(bufptr + 5, parent.hash) < 0)
 		return error("bad tree pointer in commit %s",
 			     oid_to_hex(&item->object.oid));
-	item->tree = lookup_tree(parent.hash);
+	item->tree = lookup_tree(&parent);
 	bufptr += tree_entry_len + 1; /* "tree " + "hex sha1" + "\n" */
 	pptr = &item->parents;
 
 	graft = lookup_commit_graft(item->object.oid.hash);
 	while (bufptr + parent_entry_len < tail && !memcmp(bufptr, "parent ", 7)) {
 		struct commit *new_parent;
