(mp = mentry->hashtable_next; mp != NULL; mp = mp->hashtable_next) {
			if (mp->full && !mp->used
					&& mentry->name_hash == mp->name_hash
					&& strcmp(mentry->name, mp->name) == 0) {
				/* Later lines override earlier ones. */
				mp->used = 1;
				r1 = parse_line(a, entry, mtree, mp,
				    &parsed_kws);
				if (r1 < r)
					r = r1;
			}
		}