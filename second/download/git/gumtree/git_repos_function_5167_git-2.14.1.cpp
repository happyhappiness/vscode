static int add_pending_uninteresting_ref(const char *refname,
					 const struct object_id *oid,
					 int flags, void *cb_data)
{
	add_pending_oid(cb_data, refname, oid, UNINTERESTING);
	return 0;
}