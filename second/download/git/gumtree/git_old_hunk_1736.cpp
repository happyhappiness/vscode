				(dst[length] == 0 || dst[length] == '/')) {
			bad = _("can not move directory into itself");
		} else if ((src_is_dir = S_ISDIR(st.st_mode))
				&& lstat(dst, &st) == 0)
			bad = _("cannot move directory over file");
		else if (src_is_dir) {
			int first = cache_name_pos(src, length);
			if (first >= 0) {
				struct strbuf submodule_dotgit = STRBUF_INIT;
				if (!S_ISGITLINK(active_cache[first]->ce_mode))
					die (_("Huh? Directory %s is in index and no submodule?"), src);
				if (!is_staging_gitmodules_ok())
					die (_("Please, stage your changes to .gitmodules or stash them to proceed"));
				strbuf_addf(&submodule_dotgit, "%s/.git", src);
				submodule_gitfile[i] = read_gitfile(submodule_dotgit.buf);
				if (submodule_gitfile[i])
					submodule_gitfile[i] = xstrdup(submodule_gitfile[i]);
				else
					submodule_gitfile[i] = SUBMODULE_WITH_GITDIR;
				strbuf_release(&submodule_dotgit);
			} else {
				const char *src_w_slash = add_slash(src);
				int last, len_w_slash = length + 1;

				modes[i] = WORKING_DIRECTORY;

				first = cache_name_pos(src_w_slash, len_w_slash);
				if (first >= 0)
					die (_("Huh? %.*s is in index?"),
							len_w_slash, src_w_slash);

				first = -1 - first;
				for (last = first; last < active_nr; last++) {
					const char *path = active_cache[last]->name;
					if (strncmp(path, src_w_slash, len_w_slash))
						break;
				}
				if (src_w_slash != src)
					free((char *)src_w_slash);

				if (last - first < 1)
					bad = _("source directory is empty");
				else {
					int j, dst_len;

					if (last - first > 0) {
						source = xrealloc(source,
								(argc + last - first)
								* sizeof(char *));
						destination = xrealloc(destination,
								(argc + last - first)
								* sizeof(char *));
						modes = xrealloc(modes,
								(argc + last - first)
								* sizeof(enum update_mode));
						submodule_gitfile = xrealloc(submodule_gitfile,
								(argc + last - first)
								* sizeof(char *));
					}

					dst = add_slash(dst);
					dst_len = strlen(dst);

					for (j = 0; j < last - first; j++) {
						const char *path =
							active_cache[first + j]->name;
						source[argc + j] = path;
						destination[argc + j] =
							prefix_path(dst, dst_len,
								path + length + 1);
						modes[argc + j] = INDEX;
						submodule_gitfile[argc + j] = NULL;
					}
					argc += last - first;
				}
			}
		} else if (cache_name_pos(src, length) < 0)
			bad = _("not under version control");
		else if (lstat(dst, &st) == 0 &&
			 (!ignore_case || strcasecmp(src, dst))) {
			bad = _("destination exists");
