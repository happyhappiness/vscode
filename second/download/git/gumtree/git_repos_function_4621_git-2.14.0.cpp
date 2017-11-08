static int mark_complete_oid(const char *refname, const struct object_id *oid,
			     int flag, void *cb_data)
{
	return mark_complete(oid);
}