static int filter_refs(const char *refname, const unsigned char *sha1, int flags,
		       void *data)
{
	struct ref_filter *filter = (struct ref_filter *)data;
	if (wildmatch(filter->pattern, refname, 0, NULL))
		return 0;
	return filter->fn(refname, sha1, flags, filter->cb_data);
}