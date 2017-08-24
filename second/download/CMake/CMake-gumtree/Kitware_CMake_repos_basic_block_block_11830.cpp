(file->cl_offset) {
			struct file_info *first_re = NULL;
			int nexted_re = 0;

			/*
			 * Find "RE" dir for the current file, which
			 * has "CL" flag.
			 */
			while ((re = re_get_entry(iso9660))
			    != first_re) {
				if (first_re == NULL)
					first_re = re;
				if (re->offset == file->cl_offset) {
					re->parent->subdirs--;
					re->parent = file->parent;
					re->re = 0;
					if (re->parent->re_descendant) {
						nexted_re = 1;
						re->re_descendant = 1;
						if (rede_add_entry(re) < 0)
							goto fatal_rr;
						/* Move a list of descendants
						 * to a new ancestor. */
						while ((d = rede_get_entry(
						    re)) != NULL)
							if (rede_add_entry(d)
							    < 0)
								goto fatal_rr;
						break;
					}
					/* Replace the current file
					 * with "RE" dir */
					*pfile = file = re;
					/* Expose its descendant */
					while ((d = rede_get_entry(
					    file)) != NULL)
						cache_add_entry(
						    iso9660, d);
					break;
				} else
					re_add_entry(iso9660, re);
			}
			if (nexted_re) {
				/*
				 * Do not expose this at this time
				 * because we have not gotten its full-path
				 * name yet.
				 */
				continue;
			}
		} else if ((file->mode & AE_IFMT) == AE_IFDIR) {
			int r;

			/* Read file entries in this dir. */
			r = read_children(a, file);
			if (r != ARCHIVE_OK)
				return (r);

			/*
			 * Handle a special dir of Rockridge extensions,
			 * "rr_moved".
			 */
			if (file->rr_moved) {
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
		}