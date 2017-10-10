	for (i = 0; i < dir->nr; i++) {
		struct ref_entry *entry = dir->entries[i];
		if (entry->flag & REF_DIR)
			prime_ref_dir(get_ref_dir(entry));
	}
}
/*
 * Return true iff refname1 and refname2 conflict with each other.
 * Two reference names conflict if one of them exactly matches the
 * leading components of the other; e.g., "foo/bar" conflicts with
 * both "foo" and with "foo/bar/baz" but not with "foo/bar" or
 * "foo/barbados".
 */
static int names_conflict(const char *refname1, const char *refname2)
{
	for (; *refname1 && *refname1 == *refname2; refname1++, refname2++)
		;
	return (*refname1 == '\0' && *refname2 == '/')
		|| (*refname1 == '/' && *refname2 == '\0');
}

struct name_conflict_cb {
	const char *refname;
	const char *oldrefname;
	const char *conflicting_refname;
};

static int name_conflict_fn(struct ref_entry *entry, void *cb_data)
{
	struct name_conflict_cb *data = (struct name_conflict_cb *)cb_data;
	if (data->oldrefname && !strcmp(data->oldrefname, entry->name))
		return 0;
	if (names_conflict(data->refname, entry->name)) {
		data->conflicting_refname = entry->name;
		return 1;
	}
	return 0;
}

/*
 * Return true iff a reference named refname could be created without
 * conflicting with the name of an existing reference in dir.  If
 * oldrefname is non-NULL, ignore potential conflicts with oldrefname
 * (e.g., because oldrefname is scheduled for deletion in the same
 * operation).
 */
static int is_refname_available(const char *refname, const char *oldrefname,
				struct ref_dir *dir)
{
	struct name_conflict_cb data;
	data.refname = refname;
	data.oldrefname = oldrefname;
	data.conflicting_refname = NULL;

	sort_ref_dir(dir);
	if (do_for_each_entry_in_dir(dir, 0, name_conflict_fn, &data)) {
		error("'%s' exists; cannot create '%s'",
		      data.conflicting_refname, refname);
		return 0;
	}
	return 1;
}

struct packed_ref_cache {
	struct ref_entry *root;

