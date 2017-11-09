static int get_stat_data(const struct cache_entry *ce,
			 const struct object_id **oidp,
			 unsigned int *modep,
			 int cached, int match_missing,
			 unsigned *dirty_submodule, struct diff_options *diffopt)
{
	const struct object_id *oid = &ce->oid;
	unsigned int mode = ce->ce_mode;

	if (!cached && !ce_uptodate(ce)) {
		int changed;
		struct stat st;
		changed = check_removed(ce, &st);
		if (changed < 0)
			return -1;
		else if (changed) {
			if (match_missing) {
				*oidp = oid;
				*modep = mode;
				return 0;
			}
			return -1;
		}
		changed = match_stat_with_submodule(diffopt, ce, &st,
						    0, dirty_submodule);
		if (changed) {
			mode = ce_mode_from_stat(ce, st.st_mode);
			oid = &null_oid;
		}
	}

	*oidp = oid;
	*modep = mode;
	return 0;
}