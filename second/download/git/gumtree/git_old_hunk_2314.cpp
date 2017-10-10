		return 0;

	/* Add a packed ref cache entry equivalent to the loose entry. */
	peel_status = peel_entry(entry, 1);
	if (peel_status != PEEL_PEELED && peel_status != PEEL_NON_TAG)
		die("internal error peeling reference %s (%s)",
		    entry->name, sha1_to_hex(entry->u.value.sha1));
	packed_entry = find_ref(cb->packed_refs, entry->name);
	if (packed_entry) {
		/* Overwrite existing packed entry with info from loose entry */
		packed_entry->flag = REF_ISPACKED | REF_KNOWS_PEELED;
		hashcpy(packed_entry->u.value.sha1, entry->u.value.sha1);
	} else {
		packed_entry = create_ref_entry(entry->name, entry->u.value.sha1,
						REF_ISPACKED | REF_KNOWS_PEELED, 0);
		add_ref(cb->packed_refs, packed_entry);
	}
	hashcpy(packed_entry->u.value.peeled, entry->u.value.peeled);

	/* Schedule the loose reference for pruning if requested. */
	if ((cb->flags & PACK_REFS_PRUNE)) {
		int namelen = strlen(entry->name) + 1;
		struct ref_to_prune *n = xcalloc(1, sizeof(*n) + namelen);
		hashcpy(n->sha1, entry->u.value.sha1);
		strcpy(n->name, entry->name);
		n->next = cb->ref_to_prune;
		cb->ref_to_prune = n;
	}
	return 0;
}
