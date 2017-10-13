int repack_without_refs(struct string_list *refnames, struct strbuf *err)
{
	struct ref_dir *packed;
	struct string_list refs_to_delete = STRING_LIST_INIT_DUP;
	struct string_list_item *refname, *ref_to_delete;
	int ret, needs_repacking = 0, removed = 0;

	assert(err);

	/* Look for a packed ref */
	for_each_string_list_item(refname, refnames) {
		if (get_packed_ref(refname->string)) {
			needs_repacking = 1;
			break;
		}
	}

	/* Avoid locking if we have nothing to do */
	if (!needs_repacking)
		return 0; /* no refname exists in packed refs */

	if (lock_packed_refs(0)) {
		unable_to_lock_message(git_path("packed-refs"), errno, err);
		return -1;
	}
	packed = get_packed_refs(&ref_cache);

	/* Remove refnames from the cache */
	for_each_string_list_item(refname, refnames)
		if (remove_entry(packed, refname->string) != -1)
			removed = 1;
	if (!removed) {
		/*
		 * All packed entries disappeared while we were
		 * acquiring the lock.
		 */
		rollback_packed_refs();
		return 0;
	}

	/* Remove any other accumulated cruft */
	do_for_each_entry_in_dir(packed, 0, curate_packed_ref_fn, &refs_to_delete);
	for_each_string_list_item(ref_to_delete, &refs_to_delete) {
		if (remove_entry(packed, ref_to_delete->string) == -1)
			die("internal error");
	}

	/* Write what remains */
	ret = commit_packed_refs();
	if (ret)
		strbuf_addf(err, "unable to overwrite old ref-pack file: %s",
			    strerror(errno));
	return ret;
}