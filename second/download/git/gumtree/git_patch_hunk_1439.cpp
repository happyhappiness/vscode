 	else
 		tree_content_get(&b->branch_tree, s, &leaf, 1);
 	if (!leaf.versions[1].mode)
 		die("Path %s not in branch", s);
 	if (!*d) {	/* C "path/to/subdir" "" */
 		tree_content_replace(&b->branch_tree,
-			leaf.versions[1].sha1,
+			&leaf.versions[1].oid,
 			leaf.versions[1].mode,
 			leaf.tree);
 		return;
 	}
 	tree_content_set(&b->branch_tree, d,
-		leaf.versions[1].sha1,
+		&leaf.versions[1].oid,
 		leaf.versions[1].mode,
 		leaf.tree);
 }
 
 static void note_change_n(const char *p, struct branch *b, unsigned char *old_fanout)
 {
 	static struct strbuf uq = STRBUF_INIT;
 	struct object_entry *oe;
 	struct branch *s;
-	unsigned char sha1[20], commit_sha1[20];
+	struct object_id oid, commit_oid;
 	char path[60];
 	uint16_t inline_data = 0;
 	unsigned char new_fanout;
 
 	/*
 	 * When loading a branch, we don't traverse its tree to count the real
