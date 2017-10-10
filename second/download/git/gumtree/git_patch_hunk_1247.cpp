 	opts.merge = 1;
 	opts.fn = oneway_merge;
 	opts.verbose_update = (option_verbosity >= 0);
 	opts.src_index = &the_index;
 	opts.dst_index = &the_index;
 
-	tree = parse_tree_indirect(oid.hash);
+	tree = parse_tree_indirect(&oid);
 	parse_tree(tree);
 	init_tree_desc(&t, tree->buffer, tree->size);
 	if (unpack_trees(1, &t, &opts) < 0)
 		die(_("unable to checkout working tree"));
 
 	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
