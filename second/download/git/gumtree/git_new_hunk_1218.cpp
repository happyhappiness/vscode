			if (!seen[i] && path[0] &&
			    ((pathspec.items[i].magic &
			      (PATHSPEC_GLOB | PATHSPEC_ICASE)) ||
			     !file_exists(path))) {
				if (ignore_missing) {
					int dtype = DT_UNKNOWN;
					if (is_excluded(&dir, &the_index, path, &dtype))
						dir_add_ignored(&dir, &the_index,
								path, pathspec.items[i].len);
				} else
					die(_("pathspec '%s' did not match any files"),
					    pathspec.items[i].original);
			}
		}
		free(seen);
