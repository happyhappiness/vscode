static void show_killed_files(const struct index_state *istate,
			      const struct dir_struct *dir)
{
	int i;
	for (i = 0; i < dir->nr; i++) {
		struct dir_entry *ent = dir->entries[i];
		char *cp, *sp;
		int pos, len, killed = 0;

		for (cp = ent->name; cp - ent->name < ent->len; cp = sp + 1) {
			sp = strchr(cp, '/');
			if (!sp) {
				/* If ent->name is prefix of an entry in the
				 * cache, it will be killed.
				 */
				pos = index_name_pos(istate, ent->name, ent->len);
				if (0 <= pos)
					die("BUG: killed-file %.*s not found",
						ent->len, ent->name);
				pos = -pos - 1;
				while (pos < istate->cache_nr &&
				       ce_stage(istate->cache[pos]))
					pos++; /* skip unmerged */
				if (istate->cache_nr <= pos)
					break;
				/* pos points at a name immediately after
				 * ent->name in the cache.  Does it expect
				 * ent->name to be a directory?
				 */
				len = ce_namelen(istate->cache[pos]);
				if ((ent->len < len) &&
				    !strncmp(istate->cache[pos]->name,
					     ent->name, ent->len) &&
				    istate->cache[pos]->name[ent->len] == '/')
					killed = 1;
				break;
			}
			if (0 <= index_name_pos(istate, ent->name, sp - ent->name)) {
				/* If any of the leading directories in
				 * ent->name is registered in the cache,
				 * ent->name will be killed.
				 */
				killed = 1;
				break;
			}
		}
		if (killed)
			show_dir_entry(tag_killed, dir->entries[i]);
	}
}