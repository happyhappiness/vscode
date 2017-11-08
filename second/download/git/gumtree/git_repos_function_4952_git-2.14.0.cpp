static int delete_tag(const char *name, const char *ref,
		      const struct object_id *oid, const void *cb_data)
{
	if (delete_ref(NULL, ref, oid->hash, 0))
		return 1;
	printf(_("Deleted tag '%s' (was %s)\n"), name, find_unique_abbrev(oid->hash, DEFAULT_ABBREV));
	return 0;
}