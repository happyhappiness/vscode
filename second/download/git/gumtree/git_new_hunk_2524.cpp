	obj->flags |= SEEN;

	if (verbose)
		fprintf(stderr, "Checking %s %s\n",
			typename(obj->type), sha1_to_hex(obj->sha1));

	if (fsck_walk(obj, NULL, &fsck_obj_options))
		objerror(obj, "broken links");
	if (fsck_object(obj, NULL, 0, &fsck_obj_options))
		return -1;

	if (obj->type == OBJ_TREE) {
		struct tree *item = (struct tree *) obj;

		free_tree_buffer(item);
