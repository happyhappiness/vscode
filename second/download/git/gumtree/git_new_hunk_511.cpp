 * Rewrite the packed-refs file, omitting any refs listed in
 * 'refnames'. On error, leave packed-refs unchanged, write an error
 * message to 'err', and return a nonzero value.
 *
 * The refs in 'refnames' needn't be sorted. `err` must not be NULL.
 */
static int repack_without_refs(struct files_ref_store *refs,
			       struct string_list *refnames, struct strbuf *err)
{
	struct ref_dir *packed;
	struct string_list_item *refname;
	int ret, needs_repacking = 0, removed = 0;

	assert_main_repository(&refs->base, "repack_without_refs");
	assert(err);

	/* Look for a packed ref */
	for_each_string_list_item(refname, refnames) {
		if (get_packed_ref(refs, refname->string)) {
			needs_repacking = 1;
			break;
		}
	}

	/* Avoid locking if we have nothing to do */
	if (!needs_repacking)
		return 0; /* no refname exists in packed refs */

	if (lock_packed_refs(refs, 0)) {
		unable_to_lock_message(git_path("packed-refs"), errno, err);
		return -1;
	}
	packed = get_packed_refs(refs);

	/* Remove refnames from the cache */
	for_each_string_list_item(refname, refnames)
		if (remove_entry(packed, refname->string) != -1)
			removed = 1;
	if (!removed) {
		/*
		 * All packed entries disappeared while we were
		 * acquiring the lock.
		 */
		rollback_packed_refs(refs);
		return 0;
	}

	/* Write what remains */
	ret = commit_packed_refs(refs);
	if (ret)
		strbuf_addf(err, "unable to overwrite old ref-pack file: %s",
			    strerror(errno));
	return ret;
}

