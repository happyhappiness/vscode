static void find_short_object_filename(struct disambiguate_state *ds)
{
	int subdir_nr = ds->bin_pfx.hash[0];
	struct alternate_object_database *alt;
	static struct alternate_object_database *fakeent;

	if (!fakeent) {
		/*
		 * Create a "fake" alternate object database that
		 * points to our own object database, to make it
		 * easier to get a temporary working space in
		 * alt->name/alt->base while iterating over the
		 * object databases including our own.
		 */
		fakeent = alloc_alt_odb(get_object_directory());
	}
	fakeent->next = alt_odb_list;

	for (alt = fakeent; alt && !ds->ambiguous; alt = alt->next) {
		int pos;

		if (!alt->loose_objects_subdir_seen[subdir_nr]) {
			struct strbuf *buf = alt_scratch_buf(alt);
			for_each_file_in_obj_subdir(subdir_nr, buf,
						    append_loose_object,
						    NULL, NULL,
						    &alt->loose_objects_cache);
			alt->loose_objects_subdir_seen[subdir_nr] = 1;
		}

		pos = oid_array_lookup(&alt->loose_objects_cache, &ds->bin_pfx);
		if (pos < 0)
			pos = -1 - pos;
		while (!ds->ambiguous && pos < alt->loose_objects_cache.nr) {
			const struct object_id *oid;
			oid = alt->loose_objects_cache.oid + pos;
			if (!match_sha(ds->len, ds->bin_pfx.hash, oid->hash))
				break;
			update_candidates(ds, oid);
			pos++;
		}
	}
}