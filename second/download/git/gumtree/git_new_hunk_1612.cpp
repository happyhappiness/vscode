			check_object(obj);
	}
}

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
