	/* init revs to list objects for pack-objects later */
	save_commit_buffer = 0;
	init_revisions(&revs, NULL);

	/* write prerequisites */
	if (compute_and_write_prerequisites(bundle_fd, &revs, argc, argv))
		return -1;

	argc = setup_revisions(argc, argv, &revs, NULL);

	if (argc > 1)
		return error(_("unrecognized argument: %s"), argv[1]);

	object_array_remove_duplicates(&revs.pending);

	ref_count = write_bundle_refs(bundle_fd, &revs);
	if (!ref_count)
		die(_("Refusing to create empty bundle."));
	else if (ref_count < 0)
		return -1;

	/* write pack */
	if (write_pack_data(bundle_fd, &revs))
		return -1;

	if (!bundle_to_stdout) {
		if (commit_lock_file(&lock))
			die_errno(_("cannot create '%s'"), path);
	}
	return 0;
}

int unbundle(struct bundle_header *header, int bundle_fd, int flags)
{
	const char *argv_index_pack[] = {"index-pack",
					 "--fix-thin", "--stdin", NULL, NULL};
