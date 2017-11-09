static void add_refs_to_oidset(struct oidset *oids, struct ref *refs)
{
	for (; refs; refs = refs->next)
		oidset_insert(oids, &refs->old_oid);
}