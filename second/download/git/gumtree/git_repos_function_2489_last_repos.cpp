static enum exist_status directory_exists_in_index(struct index_state *istate,
						   const char *dirname, int len)
{
	int pos;

	if (ignore_case)
		return directory_exists_in_index_icase(istate, dirname, len);

	pos = index_name_pos(istate, dirname, len);
	if (pos < 0)
		pos = -pos-1;
	while (pos < istate->cache_nr) {
		const struct cache_entry *ce = istate->cache[pos++];
		unsigned char endchar;

		if (strncmp(ce->name, dirname, len))
			break;
		endchar = ce->name[len];
		if (endchar > '/')
			break;
		if (endchar == '/')
			return index_directory;
		if (!endchar && S_ISGITLINK(ce->ce_mode))
			return index_gitdir;
	}
	return index_nonexistent;
}