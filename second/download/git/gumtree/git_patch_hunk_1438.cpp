 				command_buf.buf);
 		if (p != uq.buf) {
 			strbuf_addstr(&uq, p);
 			p = uq.buf;
 		}
 		read_next_command();
-		parse_and_store_blob(&last_blob, sha1, 0);
+		parse_and_store_blob(&last_blob, &oid, 0);
 	} else {
 		enum object_type expected = S_ISDIR(mode) ?
 						OBJ_TREE: OBJ_BLOB;
 		enum object_type type = oe ? oe->type :
-					sha1_object_info(sha1, NULL);
+					sha1_object_info(oid.hash, NULL);
 		if (type < 0)
 			die("%s not found: %s",
 					S_ISDIR(mode) ?  "Tree" : "Blob",
 					command_buf.buf);
 		if (type != expected)
 			die("Not a %s (actually a %s): %s",
 				typename(expected), typename(type),
 				command_buf.buf);
 	}
 
 	if (!*p) {
-		tree_content_replace(&b->branch_tree, sha1, mode, NULL);
+		tree_content_replace(&b->branch_tree, &oid, mode, NULL);
 		return;
 	}
-	tree_content_set(&b->branch_tree, p, sha1, mode, NULL);
+	tree_content_set(&b->branch_tree, p, &oid, mode, NULL);
 }
 
 static void file_change_d(const char *p, struct branch *b)
 {
 	static struct strbuf uq = STRBUF_INIT;
 	const char *endp;
