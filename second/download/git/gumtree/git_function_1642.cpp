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