 #include "submodule.h"
 #include "submodule-config.h"
 
 static int nr_trees;
 static int read_empty;
 static struct tree *trees[MAX_UNPACK_TREES];
-static int recurse_submodules = RECURSE_SUBMODULES_DEFAULT;
 
-static int list_tree(unsigned char *sha1)
+static int list_tree(struct object_id *oid)
 {
 	struct tree *tree;
 
 	if (nr_trees >= MAX_UNPACK_TREES)
 		die("I cannot read more than %d trees", MAX_UNPACK_TREES);
-	tree = parse_tree_indirect(sha1);
+	tree = parse_tree_indirect(oid);
 	if (!tree)
 		return -1;
 	trees[nr_trees++] = tree;
 	return 0;
 }
 
