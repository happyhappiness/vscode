		const struct cache_entry *ce = active_cache[pos];
		int stage = ce_stage(ce);

		if (strcmp(ce->name, path))
			break;
		found++;
		sha1_to_hex_r(hexbuf[stage], ce->oid.hash);
		xsnprintf(ownbuf[stage], sizeof(ownbuf[stage]), "%o", ce->ce_mode);
		arguments[stage] = hexbuf[stage];
		arguments[stage + 4] = ownbuf[stage];
	} while (++pos < active_nr);
	if (!found)
		die("git merge-index: %s not in the cache", path);
