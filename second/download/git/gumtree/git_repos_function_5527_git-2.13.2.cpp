static void show_one_alternate_ref(const char *refname,
				   const struct object_id *oid,
				   void *data)
{
	struct oidset *seen = data;

	if (oidset_insert(seen, oid))
		return;

	show_ref(".have", oid);
}