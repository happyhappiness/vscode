 				die_errno("git commit-tree: failed to close '%s'",
 					  argv[i]);
 			strbuf_complete_line(&buffer);
 			continue;
 		}
 
-		if (get_sha1_tree(arg, tree_sha1))
+		if (get_sha1_tree(arg, tree_oid.hash))
 			die("Not a valid object name %s", arg);
 		if (got_tree)
 			die("Cannot give more than one trees");
 		got_tree = 1;
 	}
 
 	if (!buffer.len) {
 		if (strbuf_read(&buffer, 0, 0) < 0)
 			die_errno("git commit-tree: failed to read");
 	}
 
-	if (commit_tree(buffer.buf, buffer.len, tree_sha1, parents,
-			commit_sha1, NULL, sign_commit)) {
+	if (commit_tree(buffer.buf, buffer.len, tree_oid.hash, parents,
+			commit_oid.hash, NULL, sign_commit)) {
 		strbuf_release(&buffer);
 		return 1;
 	}
 
-	printf("%s\n", sha1_to_hex(commit_sha1));
+	printf("%s\n", oid_to_hex(&commit_oid));
 	strbuf_release(&buffer);
 	return 0;
 }
