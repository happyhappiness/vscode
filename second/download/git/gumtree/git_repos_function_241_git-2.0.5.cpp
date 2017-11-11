static int process_tree(struct walker *walker, struct tree *tree)
{
	struct tree_desc desc;
	struct name_entry entry;

	if (parse_tree(tree))
		return -1;

	init_tree_desc(&desc, tree->buffer, tree->size);
	while (tree_entry(&desc, &entry)) {
		struct object *obj = NULL;

		/* submodule commits are not stored in the superproject */
		if (S_ISGITLINK(entry.mode))
			continue;
		if (S_ISDIR(entry.mode)) {
			struct tree *tree = lookup_tree(entry.sha1);
			if (tree)
				obj = &tree->object;
		}
		else {
			struct blob *blob = lookup_blob(entry.sha1);
			if (blob)
				obj = &blob->object;
		}
		if (!obj || process(walker, obj))
			return -1;
	}
	free_tree_buffer(tree);
	return 0;
}