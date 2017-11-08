static int resolve_packed_ref(struct files_ref_store *refs,
			      const char *refname,
			      unsigned char *sha1, unsigned int *flags)
{
	struct ref_entry *entry;

	/*
	 * The loose reference file does not exist; check for a packed
	 * reference.
	 */
	entry = get_packed_ref(refs, refname);
	if (entry) {
		hashcpy(sha1, entry->u.value.oid.hash);
		*flags |= REF_ISPACKED;
		return 0;
	}
	/* refname is not a packed reference. */
	return -1;
}