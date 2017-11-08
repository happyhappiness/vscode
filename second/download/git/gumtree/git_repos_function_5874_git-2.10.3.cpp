static int entry_resolves_to_object(struct ref_entry *entry)
{
	return ref_resolves_to_object(entry->name,
				      &entry->u.value.oid, entry->flag);
}