 	 *  NULL	- directory or bug
 	 *  empty_blob	- empty
 	 *  "<dataref>"	- data retrievable from fast-import
 	 */
 	static const char *const empty_blob = "::empty::";
 	const char *old_data = NULL;
-	uint32_t old_mode = REPO_MODE_BLB;
+	uint32_t old_mode = S_IFREG | 0644;
 
 	if (node_ctx.action == NODEACT_DELETE) {
 		if (have_text || have_props || node_ctx.srcRev)
 			die("invalid dump: deletion node has "
 				"copyfrom info, text, or properties");
-		repo_delete(node_ctx.dst.buf);
+		fast_export_delete(node_ctx.dst.buf);
 		return;
 	}
 	if (node_ctx.action == NODEACT_REPLACE) {
-		repo_delete(node_ctx.dst.buf);
+		fast_export_delete(node_ctx.dst.buf);
 		node_ctx.action = NODEACT_ADD;
 	}
 	if (node_ctx.srcRev) {
-		repo_copy(node_ctx.srcRev, node_ctx.src.buf, node_ctx.dst.buf);
+		fast_export_copy(node_ctx.srcRev, node_ctx.src.buf, node_ctx.dst.buf);
 		if (node_ctx.action == NODEACT_ADD)
 			node_ctx.action = NODEACT_CHANGE;
 	}
-	if (have_text && type == REPO_MODE_DIR)
+	if (have_text && type == S_IFDIR)
 		die("invalid dump: directories cannot have text attached");
 
 	/*
 	 * Find old content (old_data) and decide on the new mode.
 	 */
 	if (node_ctx.action == NODEACT_CHANGE && !*node_ctx.dst.buf) {
-		if (type != REPO_MODE_DIR)
+		if (type != S_IFDIR)
 			die("invalid dump: root of tree is not a regular file");
 		old_data = NULL;
 	} else if (node_ctx.action == NODEACT_CHANGE) {
 		uint32_t mode;
-		old_data = repo_read_path(node_ctx.dst.buf, &mode);
-		if (mode == REPO_MODE_DIR && type != REPO_MODE_DIR)
+		old_data = fast_export_read_path(node_ctx.dst.buf, &mode);
+		if (mode == S_IFDIR && type != S_IFDIR)
 			die("invalid dump: cannot modify a directory into a file");
-		if (mode != REPO_MODE_DIR && type == REPO_MODE_DIR)
+		if (mode != S_IFDIR && type == S_IFDIR)
 			die("invalid dump: cannot modify a file into a directory");
 		node_ctx.type = mode;
 		old_mode = mode;
 	} else if (node_ctx.action == NODEACT_ADD) {
-		if (type == REPO_MODE_DIR)
+		if (type == S_IFDIR)
 			old_data = NULL;
 		else if (have_text)
 			old_data = empty_blob;
 		else
 			die("invalid dump: adds node without text");
 	} else {
