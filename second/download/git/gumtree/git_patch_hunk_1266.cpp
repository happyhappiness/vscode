 static int stdin_diff_trees(struct tree *tree1, const char *p)
 {
 	struct object_id oid;
 	struct tree *tree2;
 	if (!isspace(*p++) || parse_oid_hex(p, &oid, &p) || *p)
 		return error("Need exactly two trees, separated by a space");
-	tree2 = lookup_tree(oid.hash);
+	tree2 = lookup_tree(&oid);
 	if (!tree2 || parse_tree(tree2))
 		return -1;
 	printf("%s %s\n", oid_to_hex(&tree1->object.oid),
 			  oid_to_hex(&tree2->object.oid));
-	diff_tree_sha1(tree1->object.oid.hash, tree2->object.oid.hash,
-		       "", &log_tree_opt.diffopt);
+	diff_tree_oid(&tree1->object.oid, &tree2->object.oid,
+		      "", &log_tree_opt.diffopt);
 	log_tree_diff_flush(&log_tree_opt);
 	return 0;
 }
 
 static int diff_tree_stdin(char *line)
 {
