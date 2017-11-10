static int add_pending_uninteresting_ref(const char *refname,
					 const struct object_id *oid,
					 int flags, void *cb_data)
{
	add_pending_sha1(cb_data, refname, oid->hash, UNINTERESTING);
	return 0;
}