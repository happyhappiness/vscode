static int ref_filter_handler(const char *refname, const struct object_id *oid, int flag, void *cb_data)
{
	struct ref_filter_cbdata *ref_cbdata = cb_data;
	struct ref_filter *filter = ref_cbdata->filter;
	struct ref_array_item *ref;
	struct commit *commit = NULL;
	unsigned int kind;

	if (flag & REF_BAD_NAME) {
		warning("ignoring ref with broken name %s", refname);
		return 0;
	}

	if (flag & REF_ISBROKEN) {
		warning("ignoring broken ref %s", refname);
		return 0;
	}

	/* Obtain the current ref kind from filter_ref_kind() and ignore unwanted refs. */
	kind = filter_ref_kind(filter, refname);
	if (!(kind & filter->kind))
		return 0;

	if (!filter_pattern_match(filter, refname))
		return 0;

	if (filter->points_at.nr && !match_points_at(&filter->points_at, oid->hash, refname))
		return 0;

	/*
	 * A merge filter is applied on refs pointing to commits. Hence
	 * obtain the commit using the 'oid' available and discard all
	 * non-commits early. The actual filtering is done later.
	 */
	if (filter->merge_commit || filter->with_commit || filter->verbose) {
		commit = lookup_commit_reference_gently(oid->hash, 1);
		if (!commit)
			return 0;
		/* We perform the filtering for the '--contains' option */
		if (filter->with_commit &&
		    !commit_contains(filter, commit))
			return 0;
	}

	/*
	 * We do not open the object yet; sort may only need refname
	 * to do its job and the resulting list may yet to be pruned
	 * by maxcount logic.
	 */
	ref = new_ref_array_item(refname, oid->hash, flag);
	ref->commit = commit;

	REALLOC_ARRAY(ref_cbdata->array->items, ref_cbdata->array->nr + 1);
	ref_cbdata->array->items[ref_cbdata->array->nr++] = ref;
	ref->kind = kind;
	return 0;
}