 		quote_c_style(path, &line, NULL, 0);
 		strbuf_addch(&line, '\n');
 	}
 	cat_blob_write(line.buf, line.len);
 }
 
-static void parse_ls(struct branch *b)
+static void parse_ls(const char *p, struct branch *b)
 {
-	const char *p;
 	struct tree_entry *root = NULL;
 	struct tree_entry leaf = {NULL};
 
 	/* ls SP (<tree-ish> SP)? <path> */
-	p = command_buf.buf + strlen("ls ");
 	if (*p == '"') {
 		if (!b)
 			die("Not in a commit: %s", command_buf.buf);
 		root = &b->branch_tree;
 	} else {
 		struct object_entry *e = parse_treeish_dataref(&p);
 		root = new_tree_entry();
 		hashcpy(root->versions[1].sha1, e->idx.sha1);
 		if (!is_null_sha1(root->versions[1].sha1))
 			root->versions[1].mode = S_IFDIR;
 		load_tree(root);
-		if (*p++ != ' ')
-			die("Missing space after tree-ish: %s", command_buf.buf);
 	}
 	if (*p == '"') {
 		static struct strbuf uq = STRBUF_INIT;
 		const char *endp;
 		strbuf_reset(&uq);
 		if (unquote_c_style(&uq, p, &endp))
