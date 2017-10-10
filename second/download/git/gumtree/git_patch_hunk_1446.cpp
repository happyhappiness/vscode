 		if (!b)
 			die("Not in a commit: %s", command_buf.buf);
 		root = &b->branch_tree;
 	} else {
 		struct object_entry *e = parse_treeish_dataref(&p);
 		root = new_tree_entry();
-		hashcpy(root->versions[1].sha1, e->idx.sha1);
-		if (!is_null_sha1(root->versions[1].sha1))
+		oidcpy(&root->versions[1].oid, &e->idx.oid);
+		if (!is_null_oid(&root->versions[1].oid))
 			root->versions[1].mode = S_IFDIR;
 		load_tree(root);
 	}
 	if (*p == '"') {
 		static struct strbuf uq = STRBUF_INIT;
 		const char *endp;
