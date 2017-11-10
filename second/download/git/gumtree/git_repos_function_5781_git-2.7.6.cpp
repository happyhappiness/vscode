static int ref_present(const char *refname,
		       const struct object_id *oid, int flags, void *cb_data)
{
	struct string_list *affected_refnames = cb_data;

	return string_list_has_string(affected_refnames, refname);
}