int peel_ref(const char *refname, unsigned char *sha1)
{
	int flag;
	unsigned char base[20];

	if (current_ref && (current_ref->name == refname
			    || !strcmp(current_ref->name, refname))) {
		if (peel_entry(current_ref, 0))
			return -1;
		hashcpy(sha1, current_ref->u.value.peeled);
		return 0;
	}

	if (read_ref_full(refname, base, 1, &flag))
		return -1;

	/*
	 * If the reference is packed, read its ref_entry from the
	 * cache in the hope that we already know its peeled value.
	 * We only try this optimization on packed references because
	 * (a) forcing the filling of the loose reference cache could
	 * be expensive and (b) loose references anyway usually do not
	 * have REF_KNOWS_PEELED.
	 */
	if (flag & REF_ISPACKED) {
		struct ref_entry *r = get_packed_ref(refname);
		if (r) {
			if (peel_entry(r, 0))
				return -1;
			hashcpy(sha1, r->u.value.peeled);
			return 0;
		}
	}

	return peel_object(base, sha1);
}