static int fsck_cache_tree(struct cache_tree *it)
{
	int i;
	int err = 0;

	if (verbose)
		fprintf(stderr, "Checking cache tree\n");

	if (0 <= it->entry_count) {
		struct object *obj = parse_object(it->sha1);
		if (!obj) {
			error("%s: invalid sha1 pointer in cache-tree",
			      sha1_to_hex(it->sha1));
			errors_found |= ERROR_REFS;
			return 1;
		}
		obj->used = 1;
		if (name_objects)
			add_decoration(fsck_walk_options.object_names,
				obj, xstrdup(":"));
		mark_object_reachable(obj);
		if (obj->type != OBJ_TREE)
			err |= objerror(obj, "non-tree in cache-tree");
	}
	for (i = 0; i < it->subtree_nr; i++)
		err |= fsck_cache_tree(it->down[i]->cache_tree);
	return err;
}