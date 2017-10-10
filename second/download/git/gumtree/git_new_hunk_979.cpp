			usage_with_options(git_symbolic_ref_usage, options);
		ret = check_symref(argv[0], 1, 0, 0);
		if (ret)
			die("Cannot delete %s, not a symbolic ref", argv[0]);
		if (!strcmp(argv[0], "HEAD"))
			die("deleting '%s' is not allowed", argv[0]);
		return delete_ref(NULL, argv[0], NULL, REF_NODEREF);
	}

	switch (argc) {
	case 1:
		ret = check_symref(argv[0], quiet, shorten, 1);
		break;
