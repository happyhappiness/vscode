			} else {
				fprintf(stderr, _("Switched to branch '%s'\n"),
					new->name);
			}
		}
		if (old->path && old->name) {
			char log_file[PATH_MAX], ref_file[PATH_MAX];

			git_snpath(log_file, sizeof(log_file), "logs/%s", old->path);
			git_snpath(ref_file, sizeof(ref_file), "%s", old->path);
			if (!file_exists(ref_file) && file_exists(log_file))
				remove_path(log_file);
		}
	}
	remove_branch_state();
	strbuf_release(&msg);
	if (!opts->quiet &&
	    (new->path || (!opts->force_detach && !strcmp(new->name, "HEAD"))))
