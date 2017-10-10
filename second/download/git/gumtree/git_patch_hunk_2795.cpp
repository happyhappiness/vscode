 	opts.index_only = 1;
 	opts.merge = 1;
 	opts.src_index = &the_index;
 	opts.dst_index = &the_index;
 
 	opts.fn = oneway_merge;
-	tree = parse_tree_indirect(current_head->object.sha1);
+	tree = parse_tree_indirect(current_head->object.oid.hash);
 	if (!tree)
 		die(_("failed to unpack HEAD tree object"));
 	parse_tree(tree);
 	init_tree_desc(&t, tree->buffer, tree->size);
 	if (unpack_trees(1, &t, &opts))
 		exit(128); /* We've already reported the error, finish dying */
