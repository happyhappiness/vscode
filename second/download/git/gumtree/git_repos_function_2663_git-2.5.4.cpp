static int resolve_missing_loose_ref(const char *refname,
				     int resolve_flags,
				     unsigned char *sha1,
				     int *flags)
{
	struct ref_entry *entry;

	/*
	 * The loose reference file does not exist; check for a packed
	 * reference.
	 */
	entry = get_packed_ref(refname);
	if (entry) {
		hashcpy(sha1, entry->u.value.oid.hash);
		if (flags)
			*flags |= REF_ISPACKED;
		return 0;
	}
	/* The reference is not a packed reference, either. */
	if (resolve_flags & RESOLVE_REF_READING) {
		errno = ENOENT;
		return -1;
	} else {
		hashclr(sha1);
		return 0;
	}
}