static int fsck_obj(struct object *obj)
{
	int err;

	if (obj->flags & SEEN)
		return 0;
	obj->flags |= SEEN;

	if (verbose)
		fprintf(stderr, "Checking %s %s\n",
			printable_type(obj), describe_object(obj));

	if (fsck_walk(obj, NULL, &fsck_obj_options))
		objerror(obj, "broken links");
	err = fsck_object(obj, NULL, 0, &fsck_obj_options);
	if (err)
		goto out;

	if (obj->type == OBJ_COMMIT) {
		struct commit *commit = (struct commit *) obj;

		if (!commit->parents && show_root)
			printf("root %s\n", describe_object(&commit->object));
	}

	if (obj->type == OBJ_TAG) {
		struct tag *tag = (struct tag *) obj;

		if (show_tags && tag->tagged) {
			printf("tagged %s %s", printable_type(tag->tagged),
				describe_object(tag->tagged));
			printf(" (%s) in %s\n", tag->tag,
				describe_object(&tag->object));
		}
	}

out:
	if (obj->type == OBJ_TREE)
		free_tree_buffer((struct tree *)obj);
	if (obj->type == OBJ_COMMIT)
		free_commit_buffer((struct commit *)obj);
	return err;
}