{
			/*
			 * If directory entries all which are descendant of
			 * rr_moved are still remaining, expose their.
			 */
			if (iso9660->re_files.first != NULL && 
			    iso9660->rr_moved != NULL &&
			    iso9660->rr_moved->rr_moved_has_re_only)
				/* Expose "rr_moved" entry. */
				cache_add_entry(iso9660, iso9660->rr_moved);
			while ((re = re_get_entry(iso9660)) != NULL) {
				/* Expose its descendant dirs. */
				while ((d = rede_get_entry(re)) != NULL)
					cache_add_entry(iso9660, d);
			}
			if (iso9660->cache_files.first != NULL)
				return (next_cache_entry(a, iso9660, pfile));
			return (ARCHIVE_EOF);
		}