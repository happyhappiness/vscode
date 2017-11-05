static int ref_resolves_to_object(struct ref_entry *entry)
{
	if (entry->flag & REF_ISBROKEN)
		return 0;
	if (!has_sha1_file(entry->u.value.oid.hash)) {
		error("%s does not point to a valid object!", entry->name);
		return 0;
	}
	return 1;
}