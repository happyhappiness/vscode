static int get_stat_data(const struct cache_entry *ce,
			 const unsigned char **sha1p,
			 unsigned int *modep,
			 int cached, int match_missing,
			 unsigned *dirty_submodule, struct diff_options *diffopt)
{
	const unsigned char *sha1 = ce->sha1;
	unsigned int mode = ce->ce_mode;

	if (!cached && !ce_uptodate(ce)) {
		int changed;
		struct stat st;
		changed = check_removed(ce, &st);
		if (changed < 0)
			return -1;
		else if (changed) {
			if (match_missing) {
				*sha1p = sha1;
				*modep = mode;
				return 0;
			}
			return -1;
		}
		changed = match_stat_with_submodule(diffopt, ce, &st,
						    0, dirty_submodule);
		if (changed) {
			mode = ce_mode_from_stat(ce, st.st_mode);
			sha1 = null_sha1;
		}
	}

	*sha1p = sha1;
	*modep = mode;
	return 0;
}