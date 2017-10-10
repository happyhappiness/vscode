	obj->flags |= SEEN;

	if (verbose)
		fprintf(stderr, "Checking %s %s\n",
			typename(obj->type), sha1_to_hex(obj->sha1));

	if (fsck_walk(obj, mark_used, NULL))
		objerror(obj, "broken links");
	if (fsck_object(obj, NULL, 0, check_strict, fsck_error_func))
		return -1;

	if (obj->type == OBJ_TREE) {
		struct tree *item = (struct tree *) obj;

		free_tree_buffer(item);
