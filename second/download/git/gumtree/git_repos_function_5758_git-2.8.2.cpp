static int do_for_each_entry(struct ref_cache *refs, const char *base,
			     each_ref_entry_fn fn, void *cb_data)
{
	struct packed_ref_cache *packed_ref_cache;
	struct ref_dir *loose_dir;
	struct ref_dir *packed_dir;
	int retval = 0;

	/*
	 * We must make sure that all loose refs are read before accessing the
	 * packed-refs file; this avoids a race condition in which loose refs
	 * are migrated to the packed-refs file by a simultaneous process, but
	 * our in-memory view is from before the migration. get_packed_ref_cache()
	 * takes care of making sure our view is up to date with what is on
	 * disk.
	 */
	loose_dir = get_loose_refs(refs);
	if (base && *base) {
		loose_dir = find_containing_dir(loose_dir, base, 0);
	}
	if (loose_dir)
		prime_ref_dir(loose_dir);

	packed_ref_cache = get_packed_ref_cache(refs);
	acquire_packed_ref_cache(packed_ref_cache);
	packed_dir = get_packed_ref_dir(packed_ref_cache);
	if (base && *base) {
		packed_dir = find_containing_dir(packed_dir, base, 0);
	}

	if (packed_dir && loose_dir) {
		sort_ref_dir(packed_dir);
		sort_ref_dir(loose_dir);
		retval = do_for_each_entry_in_dirs(
				packed_dir, loose_dir, fn, cb_data);
	} else if (packed_dir) {
		sort_ref_dir(packed_dir);
		retval = do_for_each_entry_in_dir(
				packed_dir, 0, fn, cb_data);
	} else if (loose_dir) {
		sort_ref_dir(loose_dir);
		retval = do_for_each_entry_in_dir(
				loose_dir, 0, fn, cb_data);
	}

	release_packed_ref_cache(packed_ref_cache);
	return retval;
}