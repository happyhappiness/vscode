	if (obj->type == OBJ_COMMIT) {
		struct commit *commit = (struct commit *) obj;

		free_commit_buffer(commit);

		if (!commit->parents && show_root)
			printf("root %s\n", describe_object(&commit->object));
	}

	if (obj->type == OBJ_TAG) {
		struct tag *tag = (struct tag *) obj;

		if (show_tags && tag->tagged) {
			printf("tagged %s %s", typename(tag->tagged->type),
				describe_object(tag->tagged));
			printf(" (%s) in %s\n", tag->tag,
				describe_object(&tag->object));
		}
	}

	return 0;
}

