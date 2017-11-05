static int print_ref_list(int kinds, int detached, int verbose, int abbrev, struct commit_list *with_commit, const char **pattern)
{
	int i;
	struct append_ref_cb cb;
	struct ref_list ref_list;

	memset(&ref_list, 0, sizeof(ref_list));
	ref_list.kinds = kinds;
	ref_list.verbose = verbose;
	ref_list.abbrev = abbrev;
	ref_list.with_commit = with_commit;
	if (merge_filter != NO_FILTER)
		init_revisions(&ref_list.revs, NULL);
	cb.ref_list = &ref_list;
	cb.pattern = pattern;
	cb.ret = 0;
	for_each_rawref(append_ref, &cb);
	if (merge_filter != NO_FILTER) {
		struct commit *filter;
		filter = lookup_commit_reference_gently(merge_filter_ref, 0);
		if (!filter)
			die(_("object '%s' does not point to a commit"),
			    sha1_to_hex(merge_filter_ref));

		filter->object.flags |= UNINTERESTING;
		add_pending_object(&ref_list.revs,
				   (struct object *) filter, "");
		ref_list.revs.limited = 1;

		if (prepare_revision_walk(&ref_list.revs))
			die(_("revision walk setup failed"));

		for (i = 0; i < ref_list.index; i++) {
			struct ref_item *item = &ref_list.list[i];
			struct commit *commit = item->commit;
			int is_merged = !!(commit->object.flags & UNINTERESTING);
			item->ignore = is_merged != (merge_filter == SHOW_MERGED);
		}

		for (i = 0; i < ref_list.index; i++) {
			struct ref_item *item = &ref_list.list[i];
			clear_commit_marks(item->commit, ALL_REV_FLAGS);
		}
		clear_commit_marks(filter, ALL_REV_FLAGS);

		if (verbose)
			ref_list.maxwidth = calc_maxwidth(&ref_list);
	}

	qsort(ref_list.list, ref_list.index, sizeof(struct ref_item), ref_cmp);

	detached = (detached && (kinds & REF_LOCAL_BRANCH));
	if (detached && match_patterns(pattern, "HEAD"))
		show_detached(&ref_list);

	for (i = 0; i < ref_list.index; i++) {
		int current = !detached &&
			(ref_list.list[i].kind == REF_LOCAL_BRANCH) &&
			!strcmp(ref_list.list[i].name, head);
		char *prefix = (kinds != REF_REMOTE_BRANCH &&
				ref_list.list[i].kind == REF_REMOTE_BRANCH)
				? "remotes/" : "";
		print_ref_item(&ref_list.list[i], ref_list.maxwidth, verbose,
			       abbrev, current, prefix);
	}

	free_ref_list(&ref_list);

	if (cb.ret)
		error(_("some refs could not be read"));

	return cb.ret;
}