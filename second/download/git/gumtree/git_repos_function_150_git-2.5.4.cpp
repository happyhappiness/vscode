static int check_ref(const char *refname, const struct object_id *oid,
		     int flag, void *cb_data)
{
	mark_our_ref(refname, oid);
	return 0;
}