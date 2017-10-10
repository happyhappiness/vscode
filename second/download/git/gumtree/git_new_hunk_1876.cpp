{
	struct ref_dir *packed;
	struct string_list refs_to_delete = STRING_LIST_INIT_DUP;
	struct string_list_item *ref_to_delete;
	int i, ret, removed = 0;

	assert(err);

	/* Look for a packed ref */
	for (i = 0; i < n; i++)
		if (get_packed_ref(refnames[i]))
			break;

	/* Avoid locking if we have nothing to do */
	if (i == n)
		return 0; /* no refname exists in packed refs */

	if (lock_packed_refs(0)) {
		unable_to_lock_message(git_path("packed-refs"), errno, err);
		return -1;
	}
	packed = get_packed_refs(&ref_cache);

	/* Remove refnames from the cache */
	for (i = 0; i < n; i++)
		if (remove_entry(packed, refnames[i]) != -1)
