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
