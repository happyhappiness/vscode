static int write_packed_entry_fn(struct ref_entry *entry, void *cb_data)
{
	enum peel_status peel_status = peel_entry(entry, 0);

	if (peel_status != PEEL_PEELED && peel_status != PEEL_NON_TAG)
		error("internal error: %s is not a valid packed reference!",
		      entry->name);
	write_packed_entry(cb_data, entry->name, entry->u.value.oid.hash,
			   peel_status == PEEL_PEELED ?
			   entry->u.value.peeled.hash : NULL);
	return 0;
}