static void do_merge_filter(struct ref_filter_cbdata *ref_cbdata)
{
	struct rev_info revs;
	int i, old_nr;
	struct ref_filter *filter = ref_cbdata->filter;
	struct ref_array *array = ref_cbdata->array;
	struct commit **to_clear = xcalloc(sizeof(struct commit *), array->nr);

	init_revisions(&revs, NULL);

	for (i = 0; i < array->nr; i++) {
		struct ref_array_item *item = array->items[i];
		add_pending_object(&revs, &item->commit->object, item->refname);
		to_clear[i] = item->commit;
	}

	filter->merge_commit->object.flags |= UNINTERESTING;
	add_pending_object(&revs, &filter->merge_commit->object, "");

	revs.limited = 1;
	if (prepare_revision_walk(&revs))
		die(_("revision walk setup failed"));

	old_nr = array->nr;
	array->nr = 0;

	for (i = 0; i < old_nr; i++) {
		struct ref_array_item *item = array->items[i];
		struct commit *commit = item->commit;

		int is_merged = !!(commit->object.flags & UNINTERESTING);

		if (is_merged == (filter->merge == REF_FILTER_MERGED_INCLUDE))
			array->items[array->nr++] = array->items[i];
		else
			free_array_item(item);
	}

	for (i = 0; i < old_nr; i++)
		clear_commit_marks(to_clear[i], ALL_REV_FLAGS);
	clear_commit_marks(filter->merge_commit, ALL_REV_FLAGS);
	free(to_clear);
}