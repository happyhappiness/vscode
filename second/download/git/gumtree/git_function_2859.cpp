static void prepare_bases(struct base_tree_info *bases,
			  struct commit *base,
			  struct commit **list,
			  int total)
{
	struct commit *commit;
	struct rev_info revs;
	struct diff_options diffopt;
	int i;

	if (!base)
		return;

	diff_setup(&diffopt);
	DIFF_OPT_SET(&diffopt, RECURSIVE);
	diff_setup_done(&diffopt);

	oidcpy(&bases->base_commit, &base->object.oid);

	init_revisions(&revs, NULL);
	revs.max_parents = 1;
	revs.topo_order = 1;
	for (i = 0; i < total; i++) {
		list[i]->object.flags &= ~UNINTERESTING;
		add_pending_object(&revs, &list[i]->object, "rev_list");
		list[i]->util = (void *)1;
	}
	base->object.flags |= UNINTERESTING;
	add_pending_object(&revs, &base->object, "base");

	if (prepare_revision_walk(&revs))
		die(_("revision walk setup failed"));
	/*
	 * Traverse the commits list, get prerequisite patch ids
	 * and stuff them in bases structure.
	 */
	while ((commit = get_revision(&revs)) != NULL) {
		unsigned char sha1[20];
		struct object_id *patch_id;
		if (commit->util)
			continue;
		if (commit_patch_id(commit, &diffopt, sha1))
			die(_("cannot get patch id"));
		ALLOC_GROW(bases->patch_id, bases->nr_patch_id + 1, bases->alloc_patch_id);
		patch_id = bases->patch_id + bases->nr_patch_id;
		hashcpy(patch_id->hash, sha1);
		bases->nr_patch_id++;
	}
}