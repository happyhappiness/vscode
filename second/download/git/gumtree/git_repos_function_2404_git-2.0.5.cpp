static const char *handle_missing_loose_ref(const char *refname,
					    unsigned char *sha1,
					    int reading,
					    int *flag)
{
	struct ref_entry *entry;

	/*
	 * The loose reference file does not exist; check for a packed
	 * reference.
	 */
	entry = get_packed_ref(refname);
	if (entry) {
		hashcpy(sha1, entry->u.value.sha1);
		if (flag)
			*flag |= REF_ISPACKED;
		return refname;
	}
	/* The reference is not a packed reference, either. */
	if (reading) {
		return NULL;
	} else {
		hashclr(sha1);
		return refname;
	}
}