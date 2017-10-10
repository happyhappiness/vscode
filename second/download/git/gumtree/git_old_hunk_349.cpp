	read_cache_preload(&s.pathspec);
	refresh_index(&the_index, REFRESH_QUIET|REFRESH_UNMERGED, &s.pathspec, NULL, NULL);

	fd = hold_locked_index(&index_lock, 0);

	s.is_initial = get_sha1(s.reference, sha1) ? 1 : 0;
	s.ignore_submodule_arg = ignore_submodule_arg;
	wt_status_collect(&s);

	if (0 <= fd)
		update_index_if_able(&the_index, &index_lock);

	if (s.relative_paths)
		s.prefix = prefix;

	switch (status_format) {
	case STATUS_FORMAT_SHORT:
		wt_shortstatus_print(&s);
		break;
	case STATUS_FORMAT_PORCELAIN:
		wt_porcelain_print(&s);
		break;
	case STATUS_FORMAT_UNSPECIFIED:
		die("BUG: finalize_deferred_config() should have been called");
		break;
	case STATUS_FORMAT_NONE:
	case STATUS_FORMAT_LONG:
		s.verbose = verbose;
		s.ignore_submodule_arg = ignore_submodule_arg;
		wt_status_print(&s);
		break;
	}
	return 0;
}

static const char *implicit_ident_advice(void)
{
	char *user_config = expand_user_path("~/.gitconfig");
