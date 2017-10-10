	hashcpy(ref->objectname, objectname);
	ref->flag = flag;

	return ref;
}

/*
 * A call-back given to for_each_ref().  Filter refs and keep them for
 * later object processing.
 */
static int ref_filter_handler(const char *refname, const struct object_id *oid, int flag, void *cb_data)
{
	struct ref_filter_cbdata *ref_cbdata = cb_data;
	struct ref_filter *filter = ref_cbdata->filter;
	struct ref_array_item *ref;

	if (flag & REF_BAD_NAME) {
		warning("ignoring ref with broken name %s", refname);
		return 0;
	}

	if (flag & REF_ISBROKEN) {
		warning("ignoring broken ref %s", refname);
		return 0;
	}

	if (*filter->name_patterns && !match_name_as_path(filter->name_patterns, refname))
		return 0;

	/*
	 * We do not open the object yet; sort may only need refname
	 * to do its job and the resulting list may yet to be pruned
	 * by maxcount logic.
	 */
	ref = new_ref_array_item(refname, oid->hash, flag);

	REALLOC_ARRAY(ref_cbdata->array->items, ref_cbdata->array->nr + 1);
	ref_cbdata->array->items[ref_cbdata->array->nr++] = ref;
	return 0;
}

/*  Free memory allocated for a ref_array_item */
static void free_array_item(struct ref_array_item *item)
{
