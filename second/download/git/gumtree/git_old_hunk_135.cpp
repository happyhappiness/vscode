		die(_("Refusing to create empty bundle."));

	/* end header */
	write_or_die(bundle_fd, "\n", 1);

	/* write pack */
	argv_array_pushl(&argv_pack,
			 "pack-objects", "--all-progress-implied",
			 "--stdout", "--thin", "--delta-base-offset",
			 NULL);
	memset(&rls, 0, sizeof(rls));
	rls.argv = argv_pack.argv;
	rls.in = -1;
	rls.out = bundle_fd;
	rls.git_cmd = 1;
	if (start_command(&rls))
		return error(_("Could not spawn pack-objects"));

