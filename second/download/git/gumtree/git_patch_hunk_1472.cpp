 	p->next = n;
 }
 
 static void load_subtree(struct notes_tree *t, struct leaf_node *subtree,
 		struct int_node *node, unsigned int n)
 {
-	unsigned char object_sha1[20];
+	struct object_id object_oid;
 	unsigned int prefix_len;
 	void *buf;
 	struct tree_desc desc;
 	struct name_entry entry;
 	int len, path_len;
 	unsigned char type;
 	struct leaf_node *l;
 
-	buf = fill_tree_descriptor(&desc, subtree->val_sha1);
+	buf = fill_tree_descriptor(&desc, subtree->val_oid.hash);
 	if (!buf)
 		die("Could not read %s for notes-index",
-		     sha1_to_hex(subtree->val_sha1));
+		     oid_to_hex(&subtree->val_oid));
 
-	prefix_len = subtree->key_sha1[19];
+	prefix_len = subtree->key_oid.hash[KEY_INDEX];
 	assert(prefix_len * 2 >= n);
-	memcpy(object_sha1, subtree->key_sha1, prefix_len);
+	memcpy(object_oid.hash, subtree->key_oid.hash, prefix_len);
 	while (tree_entry(&desc, &entry)) {
 		path_len = strlen(entry.path);
-		len = get_sha1_hex_segment(entry.path, path_len,
-				object_sha1 + prefix_len, 20 - prefix_len);
+		len = get_oid_hex_segment(entry.path, path_len,
+				object_oid.hash + prefix_len, GIT_SHA1_RAWSZ - prefix_len);
 		if (len < 0)
 			goto handle_non_note; /* entry.path is not a SHA1 */
 		len += prefix_len;
 
 		/*
 		 * If object SHA1 is complete (len == 20), assume note object
 		 * If object SHA1 is incomplete (len < 20), and current
 		 * component consists of 2 hex chars, assume note subtree
 		 */
-		if (len <= 20) {
+		if (len <= GIT_SHA1_RAWSZ) {
 			type = PTR_TYPE_NOTE;
 			l = (struct leaf_node *)
 				xcalloc(1, sizeof(struct leaf_node));
-			hashcpy(l->key_sha1, object_sha1);
-			hashcpy(l->val_sha1, entry.oid->hash);
-			if (len < 20) {
+			oidcpy(&l->key_oid, &object_oid);
+			oidcpy(&l->val_oid, entry.oid);
+			if (len < GIT_SHA1_RAWSZ) {
 				if (!S_ISDIR(entry.mode) || path_len != 2)
 					goto handle_non_note; /* not subtree */
-				l->key_sha1[19] = (unsigned char) len;
+				l->key_oid.hash[KEY_INDEX] = (unsigned char) len;
 				type = PTR_TYPE_SUBTREE;
 			}
 			if (note_tree_insert(t, node, n, l, type,
 					     combine_notes_concatenate))
 				die("Failed to load %s %s into notes tree "
 				    "from %s",
 				    type == PTR_TYPE_NOTE ? "note" : "subtree",
-				    sha1_to_hex(l->key_sha1), t->ref);
+				    oid_to_hex(&l->key_oid), t->ref);
 		}
 		continue;
 
 handle_non_note:
 		/*
 		 * Determine full path for this non-note entry:
