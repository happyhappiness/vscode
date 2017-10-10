
	if (force > 1)
		rm_flags = 0;

	dir.flags |= DIR_SHOW_OTHER_DIRECTORIES;

	if (remove_directories)
		dir.flags |= DIR_SHOW_IGNORED_TOO | DIR_KEEP_UNTRACKED_CONTENTS;

	if (read_cache() < 0)
		die(_("index file corrupt"));

	if (!ignored)
		setup_standard_excludes(&dir);

