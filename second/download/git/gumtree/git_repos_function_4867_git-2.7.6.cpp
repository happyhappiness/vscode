static int traverse_one_object(struct object *obj)
{
	int result;
	struct tree *tree = NULL;

	if (obj->type == OBJ_TREE) {
		tree = (struct tree *)obj;
		if (parse_tree(tree) < 0)
			return 1; /* error already displayed */
	}
	result = fsck_walk(obj, obj, &fsck_walk_options);
	if (tree)
		free_tree_buffer(tree);
	return result;
}