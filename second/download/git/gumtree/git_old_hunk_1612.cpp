			check_object(obj);
	}
}

static int fsck_obj(struct object *obj)
{
	if (obj->flags & SEEN)
		return 0;
	obj->flags |= SEEN;

	if (verbose)
		fprintf(stderr, "Checking %s %s\n",
			printable_type(obj), describe_object(obj));

	if (fsck_walk(obj, NULL, &fsck_obj_options))
		objerror(obj, "broken links");
	if (fsck_object(obj, NULL, 0, &fsck_obj_options))
		return -1;

	if (obj->type == OBJ_TREE) {
		struct tree *item = (struct tree *) obj;

		free_tree_buffer(item);
	}

	if (obj->type == OBJ_COMMIT) {
		struct commit *commit = (struct commit *) obj;

		free_commit_buffer(commit);

		if (!commit->parents && show_root)
			printf("root %s\n", describe_object(&commit->object));
	}

	if (obj->type == OBJ_TAG) {
		struct tag *tag = (struct tag *) obj;
