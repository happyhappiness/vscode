static int filter_refs(const char *refname, const struct object_id *oid,
			   int flags, void *data)
{
	struct ref_filter *filter = (struct ref_filter *)data;

	if (wildmatch(filter->pattern, refname, 0, NULL))
		return 0;
	return filter->fn(refname, oid, flags, filter->cb_data);
}