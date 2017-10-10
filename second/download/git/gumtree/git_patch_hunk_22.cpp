 
 	if (!buffer.len) {
 		if (strbuf_read(&buffer, 0, 0) < 0)
 			die_errno("git commit-tree: failed to read");
 	}
 
-	if (commit_tree(&buffer, tree_sha1, parents, commit_sha1,
-			NULL, sign_commit)) {
+	if (commit_tree(buffer.buf, buffer.len, tree_sha1, parents,
+			commit_sha1, NULL, sign_commit)) {
 		strbuf_release(&buffer);
 		return 1;
 	}
 
 	printf("%s\n", sha1_to_hex(commit_sha1));
 	strbuf_release(&buffer);
