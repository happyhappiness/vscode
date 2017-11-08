int filter_refs(struct ref_array *array, struct ref_filter *filter, unsigned int type)
{
	struct ref_filter_cbdata ref_cbdata;

	ref_cbdata.array = array;
	ref_cbdata.filter = filter;

	if (type & (FILTER_REFS_ALL | FILTER_REFS_INCLUDE_BROKEN))
		return for_each_rawref(ref_filter_handler, &ref_cbdata);
	else if (type & FILTER_REFS_ALL)
		return for_each_ref(ref_filter_handler, &ref_cbdata);
	else
		die("filter_refs: invalid type");
	return 0;
}