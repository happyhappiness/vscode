static char *get_ref_match(const struct refspec *rs, int rs_nr, const struct ref *ref,
		int send_mirror, int direction, const struct refspec **ret_pat)
{
	const struct refspec *pat;
	char *name;
	int i;
	int matching_refs = -1;
	for (i = 0; i < rs_nr; i++) {
		if (rs[i].matching &&
		    (matching_refs == -1 || rs[i].force)) {
			matching_refs = i;
			continue;
		}

		if (rs[i].pattern) {
			const char *dst_side = rs[i].dst ? rs[i].dst : rs[i].src;
			int match;
			if (direction == FROM_SRC)
				match = match_name_with_pattern(rs[i].src, ref->name, dst_side, &name);
			else
				match = match_name_with_pattern(dst_side, ref->name, rs[i].src, &name);
			if (match) {
				matching_refs = i;
				break;
			}
		}
	}
	if (matching_refs == -1)
		return NULL;

	pat = rs + matching_refs;
	if (pat->matching) {
		/*
		 * "matching refs"; traditionally we pushed everything
		 * including refs outside refs/heads/ hierarchy, but
		 * that does not make much sense these days.
		 */
		if (!send_mirror && !starts_with(ref->name, "refs/heads/"))
			return NULL;
		name = xstrdup(ref->name);
	}
	if (ret_pat)
		*ret_pat = pat;
	return name;
}