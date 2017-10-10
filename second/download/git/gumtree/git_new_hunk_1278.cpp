	int err = 0;

	if (verbose)
		fprintf(stderr, "Checking cache tree\n");

	if (0 <= it->entry_count) {
		struct object *obj = parse_object(&it->oid);
		if (!obj) {
			error("%s: invalid sha1 pointer in cache-tree",
			      oid_to_hex(&it->oid));
			errors_found |= ERROR_REFS;
			return 1;
		}
		obj->used = 1;
		if (name_objects)
			add_decoration(fsck_walk_options.object_names,
