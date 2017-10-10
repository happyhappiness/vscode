	for (i = 0; i < nr_trees; i++) {
		parse_tree(trees[i]);
		init_tree_desc(t+i, trees[i]->buffer, trees[i]->size);
	}
	if (unpack_trees(nr_trees, t, &opts))
		return -1;
	if (write_cache(fd, active_cache, active_nr) ||
		commit_locked_index(lock_file))
		die(_("unable to write new index file"));
	return 0;
}
