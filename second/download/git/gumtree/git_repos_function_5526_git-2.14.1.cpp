static int append_tag_ref(const char *refname, const struct object_id *oid,
			  int flag, void *cb_data)
{
	if (!starts_with(refname, "refs/tags/"))
		return 0;
	return append_ref(refname + 5, oid, 0);
}