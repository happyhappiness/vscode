static void add_cache_refs(struct rev_info *revs)
{
	int i;

	read_cache();
	for (i = 0; i < active_nr; i++) {
		/*
		 * The index can contain blobs and GITLINKs, GITLINKs are hashes
		 * that don't actually point to objects in the repository, it's
		 * almost guaranteed that they are NOT blobs, so we don't call
		 * lookup_blob() on them, to avoid populating the hash table
		 * with invalid information
		 */
		if (S_ISGITLINK(active_cache[i]->ce_mode))
			continue;

		lookup_blob(active_cache[i]->sha1);
		/*
		 * We could add the blobs to the pending list, but quite
		 * frankly, we don't care. Once we've looked them up, and
		 * added them as objects, we've really done everything
		 * there is to do for a blob
		 */
	}
	if (active_cache_tree)
		add_cache_tree(active_cache_tree, revs);
}