static int rev_list_insert_ref_oid(const char *refname, const struct object_id *oid,
				   int flag, void *cb_data)
{
	return rev_list_insert_ref(refname, oid);
}