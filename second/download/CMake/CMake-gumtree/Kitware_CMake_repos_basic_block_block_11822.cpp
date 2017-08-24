{
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
				}