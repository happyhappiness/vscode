 #include "log-tree.h"
 #include "builtin.h"
 #include "submodule.h"
 
 static struct rev_info log_tree_opt;
 
-static int diff_tree_commit_sha1(const unsigned char *sha1)
+static int diff_tree_commit_sha1(const struct object_id *oid)
 {
-	struct commit *commit = lookup_commit_reference(sha1);
+	struct commit *commit = lookup_commit_reference(oid->hash);
 	if (!commit)
 		return -1;
 	return log_tree_commit(&log_tree_opt, commit);
 }
 
 /* Diff one or more commits. */
-static int stdin_diff_commit(struct commit *commit, char *line, int len)
+static int stdin_diff_commit(struct commit *commit, const char *p)
 {
-	unsigned char sha1[20];
-	if (isspace(line[40]) && !get_sha1_hex(line+41, sha1)) {
-		/* Graft the fake parents locally to the commit */
-		int pos = 41;
-		struct commit_list **pptr;
-
-		/* Free the real parent list */
-		free_commit_list(commit->parents);
-		commit->parents = NULL;
-		pptr = &(commit->parents);
-		while (line[pos] && !get_sha1_hex(line + pos, sha1)) {
-			struct commit *parent = lookup_commit(sha1);
-			if (parent) {
-				pptr = &commit_list_insert(parent, pptr)->next;
-			}
-			pos += 41;
+	struct object_id oid;
+	struct commit_list **pptr = NULL;
+
+	/* Graft the fake parents locally to the commit */
+	while (isspace(*p++) && !parse_oid_hex(p, &oid, &p)) {
+		struct commit *parent = lookup_commit(oid.hash);
+		if (!pptr) {
+			/* Free the real parent list */
+			free_commit_list(commit->parents);
+			commit->parents = NULL;
+			pptr = &(commit->parents);
+		}
+		if (parent) {
+			pptr = &commit_list_insert(parent, pptr)->next;
 		}
 	}
 	return log_tree_commit(&log_tree_opt, commit);
 }
 
 /* Diff two trees. */
-static int stdin_diff_trees(struct tree *tree1, char *line, int len)
+static int stdin_diff_trees(struct tree *tree1, const char *p)
 {
-	unsigned char sha1[20];
+	struct object_id oid;
 	struct tree *tree2;
-	if (len != 82 || !isspace(line[40]) || get_sha1_hex(line + 41, sha1))
+	if (!isspace(*p++) || parse_oid_hex(p, &oid, &p) || *p)
 		return error("Need exactly two trees, separated by a space");
-	tree2 = lookup_tree(sha1);
+	tree2 = lookup_tree(oid.hash);
 	if (!tree2 || parse_tree(tree2))
 		return -1;
 	printf("%s %s\n", oid_to_hex(&tree1->object.oid),
 			  oid_to_hex(&tree2->object.oid));
 	diff_tree_sha1(tree1->object.oid.hash, tree2->object.oid.hash,
 		       "", &log_tree_opt.diffopt);
