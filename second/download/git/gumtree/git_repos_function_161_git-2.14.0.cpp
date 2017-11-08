static int check_ref(const char *refname_full, const struct object_id *oid,
		     int flag, void *cb_data)
{
	const char *refname = strip_namespace(refname_full);

	mark_our_ref(refname, refname_full, oid);
	return 0;
}