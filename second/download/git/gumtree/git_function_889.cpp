static int files_pack_refs(struct ref_store *ref_store, unsigned int flags)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE | REF_STORE_ODB,
			       "pack_refs");
	struct ref_iterator *iter;
	struct ref_dir *packed_refs;
	int ok;
	struct ref_to_prune *refs_to_prune = NULL;

	lock_packed_refs(refs, LOCK_DIE_ON_ERROR);
	packed_refs = get_packed_refs(refs);

	iter = cache_ref_iterator_begin(get_loose_ref_cache(refs), NULL, 0);
	while ((ok = ref_iterator_advance(iter)) == ITER_OK) {
		/*
		 * If the loose reference can be packed, add an entry
		 * in the packed ref cache. If the reference should be
		 * pruned, also add it to refs_to_prune.
		 */
		struct ref_entry *packed_entry;
		int is_tag_ref = starts_with(iter->refname, "refs/tags/");

		/* Do not pack per-worktree refs: */
		if (ref_type(iter->refname) != REF_TYPE_NORMAL)
			continue;

		/* ALWAYS pack tags */
		if (!(flags & PACK_REFS_ALL) && !is_tag_ref)
			continue;

		/* Do not pack symbolic or broken refs: */
		if (iter->flags & REF_ISSYMREF)
			continue;

		if (!ref_resolves_to_object(iter->refname, iter->oid, iter->flags))
			continue;

		/*
		 * Create an entry in the packed-refs cache equivalent
		 * to the one from the loose ref cache, except that
		 * we don't copy the peeled status, because we want it
		 * to be re-peeled.
		 */
		packed_entry = find_ref_entry(packed_refs, iter->refname);
		if (packed_entry) {
			/* Overwrite existing packed entry with info from loose entry */
			packed_entry->flag = REF_ISPACKED;
			oidcpy(&packed_entry->u.value.oid, iter->oid);
		} else {
			packed_entry = create_ref_entry(iter->refname, iter->oid->hash,
							REF_ISPACKED, 0);
			add_ref_entry(packed_refs, packed_entry);
		}
		oidclr(&packed_entry->u.value.peeled);

		/* Schedule the loose reference for pruning if requested. */
		if ((flags & PACK_REFS_PRUNE)) {
			struct ref_to_prune *n;
			FLEX_ALLOC_STR(n, name, iter->refname);
			hashcpy(n->sha1, iter->oid->hash);
			n->next = refs_to_prune;
			refs_to_prune = n;
		}
	}
	if (ok != ITER_DONE)
		die("error while iterating over references");

	if (commit_packed_refs(refs))
		die_errno("unable to overwrite old ref-pack file");

	prune_refs(refs, refs_to_prune);
	return 0;
}