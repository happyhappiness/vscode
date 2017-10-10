	 * When reading only one tree (either the most basic form,
	 * "-m ent" or "--reset ent" form), we can obtain a fully
	 * valid cache-tree because the index must match exactly
	 * what came from the tree.
	 */
	if (nr_trees == 1 && !opts.prefix)
		prime_cache_tree(&the_index, trees[0]);

	if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
		die("unable to write new index file");
	return 0;
}
