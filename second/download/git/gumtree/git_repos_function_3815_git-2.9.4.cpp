static int one_local_ref(const char *refname, const struct object_id *oid,
			 int flag, void *cb_data)
{
	struct ref ***local_tail = cb_data;
	struct ref *ref;

	/* we already know it starts with refs/ to get here */
	if (check_refname_format(refname + 5, 0))
		return 0;

	ref = alloc_ref(refname);
	oidcpy(&ref->new_oid, oid);
	**local_tail = ref;
	*local_tail = &ref->next;
	return 0;
}