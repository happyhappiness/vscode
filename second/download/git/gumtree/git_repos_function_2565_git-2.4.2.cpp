static int is_refname_available(const char *refname,
				const struct string_list *skip,
				struct ref_dir *dir)
{
	const char *slash;
	size_t len;
	int pos;
	char *dirname;

	for (slash = strchr(refname, '/'); slash; slash = strchr(slash + 1, '/')) {
		/*
		 * We are still at a leading dir of the refname; we are
		 * looking for a conflict with a leaf entry.
		 *
		 * If we find one, we still must make sure it is
		 * not in "skip".
		 */
		pos = search_ref_dir(dir, refname, slash - refname);
		if (pos >= 0) {
			struct ref_entry *entry = dir->entries[pos];
			if (entry_matches(entry, skip))
				return 1;
			report_refname_conflict(entry, refname);
			return 0;
		}


		/*
		 * Otherwise, we can try to continue our search with
		 * the next component; if we come up empty, we know
		 * there is nothing under this whole prefix.
		 */
		pos = search_ref_dir(dir, refname, slash + 1 - refname);
		if (pos < 0)
			return 1;

		dir = get_ref_dir(dir->entries[pos]);
	}

	/*
	 * We are at the leaf of our refname; we want to
	 * make sure there are no directories which match it.
	 */
	len = strlen(refname);
	dirname = xmallocz(len + 1);
	sprintf(dirname, "%s/", refname);
	pos = search_ref_dir(dir, dirname, len + 1);
	free(dirname);

	if (pos >= 0) {
		/*
		 * We found a directory named "refname". It is a
		 * problem iff it contains any ref that is not
		 * in "skip".
		 */
		struct ref_entry *entry = dir->entries[pos];
		struct ref_dir *dir = get_ref_dir(entry);
		struct nonmatching_ref_data data;

		data.skip = skip;
		sort_ref_dir(dir);
		if (!do_for_each_entry_in_dir(dir, 0, nonmatching_ref_fn, &data))
			return 1;

		report_refname_conflict(data.found, refname);
		return 0;
	}

	/*
	 * There is no point in searching for another leaf
	 * node which matches it; such an entry would be the
	 * ref we are looking for, not a conflict.
	 */
	return 1;
}