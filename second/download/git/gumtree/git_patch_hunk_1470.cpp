 		die(_("failed to read the cache"));
 	resolve_undo_clear();
 
 	return ret;
 }
 
-int checkout_fast_forward(const unsigned char *head,
-			  const unsigned char *remote,
+int checkout_fast_forward(const struct object_id *head,
+			  const struct object_id *remote,
 			  int overwrite_ignore)
 {
 	struct tree *trees[MAX_UNPACK_TREES];
 	struct unpack_trees_options opts;
 	struct tree_desc t[MAX_UNPACK_TREES];
 	int i, nr_trees = 0;
