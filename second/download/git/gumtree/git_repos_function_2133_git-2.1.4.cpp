static void walk_commit_list(struct rev_info *revs,
			     struct connectivity_progress *cp)
{
	int i;
	struct commit *commit;
	struct object_array objects = OBJECT_ARRAY_INIT;

	/* Walk all commits, process their trees */
	while ((commit = get_revision(revs)) != NULL) {
		process_tree(commit->tree, &objects, NULL, "", cp);
		update_progress(cp);
	}

	/* Then walk all the pending objects, recursively processing them too */
	for (i = 0; i < revs->pending.nr; i++) {
		struct object_array_entry *pending = revs->pending.objects + i;
		struct object *obj = pending->item;
		const char *name = pending->name;
		if (obj->type == OBJ_TAG) {
			process_tag((struct tag *) obj, &objects, name, cp);
			continue;
		}
		if (obj->type == OBJ_TREE) {
			process_tree((struct tree *)obj, &objects, NULL, name, cp);
			continue;
		}
		if (obj->type == OBJ_BLOB) {
			process_blob((struct blob *)obj, &objects, NULL, name, cp);
			continue;
		}
		die("unknown pending object %s (%s)", sha1_to_hex(obj->sha1), name);
	}
}