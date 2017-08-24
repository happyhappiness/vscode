(file->rr_moved) {
				/*
				 * If this has only the subdirectories which
				 * have "RE" flags, do not expose at this time.
				 */
				if (file->rr_moved_has_re_only)
					continue;
				/* Otherwise expose "rr_moved" entry. */
			} else if (file->re) {
				/*
				 * Do not expose this at this time
				 * because we have not gotten its full-path
				 * name yet.
				 */
				re_add_entry(iso9660, file);
				continue;
			} else if (file->re_descendant) {
				/*
				 * If the top level "RE" entry of this entry
				 * is not exposed, we, accordingly, should not
				 * expose this entry at this time because
				 * we cannot make its proper full-path name.
				 */
				if (rede_add_entry(file) == 0)
					continue;
				/* Otherwise we can expose this entry because
				 * it seems its top level "RE" has already been
				 * exposed. */
			}