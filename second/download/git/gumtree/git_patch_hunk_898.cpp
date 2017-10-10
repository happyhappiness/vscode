 	return 0;
 }
 
 static int diff_tree_stdin(char *line)
 {
 	int len = strlen(line);
-	unsigned char sha1[20];
+	struct object_id oid;
 	struct object *obj;
+	const char *p;
 
 	if (!len || line[len-1] != '\n')
 		return -1;
 	line[len-1] = 0;
-	if (get_sha1_hex(line, sha1))
+	if (parse_oid_hex(line, &oid, &p))
 		return -1;
-	obj = parse_object(sha1);
+	obj = parse_object(oid.hash);
 	if (!obj)
 		return -1;
 	if (obj->type == OBJ_COMMIT)
-		return stdin_diff_commit((struct commit *)obj, line, len);
+		return stdin_diff_commit((struct commit *)obj, p);
 	if (obj->type == OBJ_TREE)
-		return stdin_diff_trees((struct tree *)obj, line, len);
+		return stdin_diff_trees((struct tree *)obj, p);
 	error("Object %s is a %s, not a commit or tree",
-	      sha1_to_hex(sha1), typename(obj->type));
+	      oid_to_hex(&oid), typename(obj->type));
 	return -1;
 }
 
 static const char diff_tree_usage[] =
 "git diff-tree [--stdin] [-m] [-c] [--cc] [-s] [-v] [--pretty] [-t] [-r] [--root] "
 "[<common-diff-options>] <tree-ish> [<tree-ish>] [<path>...]\n"
