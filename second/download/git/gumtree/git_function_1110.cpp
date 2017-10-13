static int pack_if_possible_fn(struct ref_entry *entry, void *cb_data)
{
	struct pack_refs_cb_data *cb = cb_data;
	enum peel_status peel_status;
	struct ref_entry *packed_entry;
	int is_tag_ref = starts_with(entry->name, "refs/tags/");

	/* Do not pack per-worktree refs: */
	if (ref_type(entry->name) != REF_TYPE_NORMAL)
		return 0;

	/* ALWAYS pack tags */
	if (!(cb->flags & PACK_REFS_ALL) && !is_tag_ref)
		return 0;

	/* Do not pack symbolic or broken refs: */
	if ((entry->flag & REF_ISSYMREF) || !entry_resolves_to_object(entry))
		return 0;

	/* Add a packed ref cache entry equivalent to the loose entry. */
	peel_status = peel_entry(entry, 1);
	if (peel_status != PEEL_PEELED && peel_status != PEEL_NON_TAG)
		die("internal error peeling reference %s (%s)",
		    entry->name, oid_to_hex(&entry->u.value.oid));
	packed_entry = find_ref(cb->packed_refs, entry->name);
	if (packed_entry) {
		/* Overwrite existing packed entry with info from loose entry */
		packed_entry->flag = REF_ISPACKED | REF_KNOWS_PEELED;
		oidcpy(&packed_entry->u.value.oid, &entry->u.value.oid);
	} else {
		packed_entry = create_ref_entry(entry->name, entry->u.value.oid.hash,
						REF_ISPACKED | REF_KNOWS_PEELED, 0);
		add_ref(cb->packed_refs, packed_entry);
	}
	oidcpy(&packed_entry->u.value.peeled, &entry->u.value.peeled);

	/* Schedule the loose reference for pruning if requested. */
	if ((cb->flags & PACK_REFS_PRUNE)) {
		struct ref_to_prune *n;
		FLEX_ALLOC_STR(n, name, entry->name);
		hashcpy(n->sha1, entry->u.value.oid.hash);
		n->next = cb->ref_to_prune;
		cb->ref_to_prune = n;
	}
	return 0;
}