int index_name_is_other(const struct index_state *istate, const char *name,
		int namelen)
{
	int pos;
	if (namelen && name[namelen - 1] == '/')
		namelen--;
	pos = index_name_pos(istate, name, namelen);
	if (0 <= pos)
		return 0;	/* exact match */
	pos = -pos - 1;
	if (pos < istate->cache_nr) {
		struct cache_entry *ce = istate->cache[pos];
		if (ce_namelen(ce) == namelen &&
		    !memcmp(ce->name, name, namelen))
			return 0; /* Yup, this one exists unmerged */
	}
	return 1;
}