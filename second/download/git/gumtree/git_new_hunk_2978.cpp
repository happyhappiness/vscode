		free_array_item(array->items[i]);
	free(array->items);
	array->items = NULL;
	array->nr = array->alloc = 0;
}

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

/*
 * API for filtering a set of refs. Based on the type of refs the user
 * has requested, we iterate through those refs and apply filters
 * as per the given ref_filter structure and finally store the
 * filtered refs in the ref_array structure.
 */
int filter_refs(struct ref_array *array, struct ref_filter *filter, unsigned int type)
{
	struct ref_filter_cbdata ref_cbdata;
	int ret = 0;
	unsigned int broken = 0;

	ref_cbdata.array = array;
	ref_cbdata.filter = filter;

	if (type & FILTER_REFS_INCLUDE_BROKEN)
		broken = 1;
	filter->kind = type & FILTER_REFS_KIND_MASK;

	/*  Simple per-ref filtering */
	if (!filter->kind)
		die("filter_refs: invalid type");
	else {
		/*
		 * For common cases where we need only branches or remotes or tags,
		 * we only iterate through those refs. If a mix of refs is needed,
		 * we iterate over all refs and filter out required refs with the help
		 * of filter_ref_kind().
		 */
		if (filter->kind == FILTER_REFS_BRANCHES)
			ret = for_each_fullref_in("refs/heads/", ref_filter_handler, &ref_cbdata, broken);
		else if (filter->kind == FILTER_REFS_REMOTES)
			ret = for_each_fullref_in("refs/remotes/", ref_filter_handler, &ref_cbdata, broken);
		else if (filter->kind == FILTER_REFS_TAGS)
			ret = for_each_fullref_in("refs/tags/", ref_filter_handler, &ref_cbdata, broken);
		else if (filter->kind & FILTER_REFS_ALL)
			ret = for_each_fullref_in("", ref_filter_handler, &ref_cbdata, broken);
		if (!ret && (filter->kind & FILTER_REFS_DETACHED_HEAD))
			head_ref(ref_filter_handler, &ref_cbdata);
	}


	/*  Filters that need revision walking */
	if (filter->merge_commit)
		do_merge_filter(&ref_cbdata);

	return ret;
}

static int cmp_ref_sorting(struct ref_sorting *s, struct ref_array_item *a, struct ref_array_item *b)
{
	struct atom_value *va, *vb;
	int cmp;
	cmp_type cmp_type = used_atom_type[s->atom];

	get_ref_atom_value(a, s->atom, &va);
	get_ref_atom_value(b, s->atom, &vb);
	if (s->version)
		cmp = versioncmp(va->s, vb->s);
	else if (cmp_type == FIELD_STR)
		cmp = strcmp(va->s, vb->s);
	else {
		if (va->ul < vb->ul)
			cmp = -1;
		else if (va->ul == vb->ul)
			cmp = strcmp(a->refname, b->refname);
		else
			cmp = 1;
	}

	return (s->reverse) ? -cmp : cmp;
}

static struct ref_sorting *ref_sorting;
static int compare_refs(const void *a_, const void *b_)
{
