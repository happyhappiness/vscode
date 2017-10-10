				(dst[length] == 0 || dst[length] == '/')) {
			bad = _("can not move directory into itself");
		} else if ((src_is_dir = S_ISDIR(st.st_mode))
				&& lstat(dst, &st) == 0)
			bad = _("cannot move directory over file");
		else if (src_is_dir) {
			int first = cache_name_pos(src, length), last;

			if (first >= 0)
				prepare_move_submodule(src, first,
						       submodule_gitfile + i);
			else if (index_range_of_same_dir(src, length,
							 &first, &last) < 1)
				bad = _("source directory is empty");
			else { /* last - first >= 1 */
				int j, dst_len, n;

				modes[i] = WORKING_DIRECTORY;
				n = argc + last - first;
				REALLOC_ARRAY(source, n);
				REALLOC_ARRAY(destination, n);
				REALLOC_ARRAY(modes, n);
				REALLOC_ARRAY(submodule_gitfile, n);

				dst = add_slash(dst);
				dst_len = strlen(dst);

				for (j = 0; j < last - first; j++) {
					const char *path = active_cache[first + j]->name;
					source[argc + j] = path;
					destination[argc + j] =
						prefix_path(dst, dst_len, path + length + 1);
					modes[argc + j] = INDEX;
					submodule_gitfile[argc + j] = NULL;
				}
				argc += last - first;
			}
		} else if (cache_name_pos(src, length) < 0)
			bad = _("not under version control");
		else if (lstat(dst, &st) == 0 &&
			 (!ignore_case || strcasecmp(src, dst))) {
			bad = _("destination exists");
