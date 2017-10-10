static void mark_tree_contents_uninteresting(struct tree *tree)
{
	struct tree_desc desc;
	struct name_entry entry;
	struct object *obj = &tree->object;

	if (!has_sha1_file(obj->sha1))
		return;
	if (parse_tree(tree) < 0)
		die("bad tree %s", sha1_to_hex(obj->sha1));

	init_tree_desc(&desc, tree->buffer, tree->size);
	while (tree_entry(&desc, &entry)) {
		switch (object_type(entry.mode)) {
		case OBJ_TREE:
			mark_tree_uninteresting(lookup_tree(entry.sha1));
