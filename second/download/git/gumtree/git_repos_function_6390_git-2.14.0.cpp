static int files_peel_ref(struct ref_store *ref_store,
			  const char *refname, unsigned char *sha1)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_READ | REF_STORE_ODB,
			       "peel_ref");
	int flag;
	unsigned char base[20];

	if (current_ref_iter && current_ref_iter->refname == refname) {
		struct object_id peeled;

		if (ref_iterator_peel(current_ref_iter, &peeled))
			return -1;
		hashcpy(sha1, peeled.hash);
		return 0;
	}

	if (refs_read_ref_full(ref_store, refname,
			       RESOLVE_REF_READING, base, &flag))
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
		struct ref_entry *r = get_packed_ref(refs, refname);
		if (r) {
			if (peel_entry(r, 0))
				return -1;
			hashcpy(sha1, r->u.value.peeled.hash);
			return 0;
		}
	}

	return peel_object(base, sha1);
}