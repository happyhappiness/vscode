fprintf(stderr, _("Migrating git directory of '%s%s' from\n'%s' to\n'%s'\n"),
		prefix ? prefix : "", path,
		real_old_git_dir, real_new_git_dir);