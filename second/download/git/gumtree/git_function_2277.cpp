int cmd_prune(int argc, const char **argv, const char *prefix)
{
	struct rev_info revs;
	struct progress *progress = NULL;
	const struct option options[] = {
		OPT__DRY_RUN(&show_only, N_("do not remove, show only")),
		OPT__VERBOSE(&verbose, N_("report pruned objects")),
		OPT_BOOL(0, "progress", &show_progress, N_("show progress")),
		OPT_EXPIRY_DATE(0, "expire", &expire,
				N_("expire objects older than <time>")),
		OPT_END()
	};
	char *s;

	expire = ULONG_MAX;
	save_commit_buffer = 0;
	check_replace_refs = 0;
	ref_paranoia = 1;
	init_revisions(&revs, prefix);

	argc = parse_options(argc, argv, prefix, options, prune_usage, 0);

	if (repository_format_precious_objects)
		die(_("cannot prune in a precious-objects repo"));

	while (argc--) {
		unsigned char sha1[20];
		const char *name = *argv++;

		if (!get_sha1(name, sha1)) {
			struct object *object = parse_object_or_die(sha1, name);
			add_pending_object(&revs, object, "");
		}
		else
			die("unrecognized argument: %s", name);
	}

	if (show_progress == -1)
		show_progress = isatty(2);
	if (show_progress)
		progress = start_progress_delay(_("Checking connectivity"), 0, 0, 2);

	mark_reachable_objects(&revs, 1, expire, progress);
	stop_progress(&progress);
	for_each_loose_file_in_objdir(get_object_directory(), prune_object,
				      prune_cruft, prune_subdir, NULL);

	prune_packed_objects(show_only ? PRUNE_PACKED_DRY_RUN : 0);
	remove_temporary_files(get_object_directory());
	s = mkpathdup("%s/pack", get_object_directory());
	remove_temporary_files(s);
	free(s);

	if (is_repository_shallow())
		prune_shallow(show_only);

	return 0;
}