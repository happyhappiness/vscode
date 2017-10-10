		for (cp = ent->name; cp - ent->name < ent->len; cp = sp + 1) {
			sp = strchr(cp, '/');
			if (!sp) {
				/* If ent->name is prefix of an entry in the
				 * cache, it will be killed.
				 */
				pos = cache_name_pos(ent->name, ent->len);
				if (0 <= pos)
					die("BUG: killed-file %.*s not found",
						ent->len, ent->name);
				pos = -pos - 1;
				while (pos < active_nr &&
				       ce_stage(active_cache[pos]))
					pos++; /* skip unmerged */
				if (active_nr <= pos)
					break;
				/* pos points at a name immediately after
				 * ent->name in the cache.  Does it expect
				 * ent->name to be a directory?
				 */
				len = ce_namelen(active_cache[pos]);
				if ((ent->len < len) &&
				    !strncmp(active_cache[pos]->name,
					     ent->name, ent->len) &&
				    active_cache[pos]->name[ent->len] == '/')
					killed = 1;
				break;
			}
			if (0 <= cache_name_pos(ent->name, sp - ent->name)) {
				/* If any of the leading directories in
				 * ent->name is registered in the cache,
				 * ent->name will be killed.
				 */
				killed = 1;
				break;
