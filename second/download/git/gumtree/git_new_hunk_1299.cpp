	 */
	while ((commit = get_revision(&revs)) != NULL) {
		struct object_id oid;
		struct object_id *patch_id;
		if (commit->util)
			continue;
		if (commit_patch_id(commit, &diffopt, &oid, 0))
			die(_("cannot get patch id"));
		ALLOC_GROW(bases->patch_id, bases->nr_patch_id + 1, bases->alloc_patch_id);
		patch_id = bases->patch_id + bases->nr_patch_id;
		oidcpy(patch_id, &oid);
		bases->nr_patch_id++;
	}
