static void get_tags_and_duplicates(struct rev_cmdline_info *info)
{
	int i;

	for (i = 0; i < info->nr; i++) {
		struct rev_cmdline_entry *e = info->rev + i;
		struct object_id oid;
		struct commit *commit;
		char *full_name;

		if (e->flags & UNINTERESTING)
			continue;

		if (dwim_ref(e->name, strlen(e->name), oid.hash, &full_name) != 1)
			continue;

		if (refspecs) {
			char *private;
			private = apply_refspecs(refspecs, refspecs_nr, full_name);
			if (private) {
				free(full_name);
				full_name = private;
			}
		}

		commit = get_commit(e, full_name);
		if (!commit) {
			warning("%s: Unexpected object of type %s, skipping.",
				e->name,
				typename(e->item->type));
			continue;
		}

		switch(commit->object.type) {
		case OBJ_COMMIT:
			break;
		case OBJ_BLOB:
			export_blob(&commit->object.oid);
			continue;
		default: /* OBJ_TAG (nested tags) is already handled */
			warning("Tag points to object of unexpected type %s, skipping.",
				typename(commit->object.type));
			continue;
		}

		/*
		 * This ref will not be updated through a commit, lets make
		 * sure it gets properly updated eventually.
		 */
		if (commit->util || commit->object.flags & SHOWN)
			string_list_append(&extra_refs, full_name)->util = commit;
		if (!commit->util)
			commit->util = full_name;
	}
}