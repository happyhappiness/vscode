static int add_ref(const char *refname, const struct object_id *oid,
		   int flags, void *cb_data)
{
	struct commit_array *ca = cb_data;
	ALLOC_GROW(ca->commits, ca->nr + 1, ca->alloc);
	ca->commits[ca->nr] = lookup_commit_reference_gently(oid, 1);
	if (ca->commits[ca->nr])
		ca->nr++;
	return 0;
}