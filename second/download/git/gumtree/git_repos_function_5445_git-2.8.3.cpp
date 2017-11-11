int cmd_check_ref_format(int argc, const char **argv, const char *prefix)
{
	int i;
	int normalize = 0;
	int flags = 0;
	const char *refname;

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage(builtin_check_ref_format_usage);

	if (argc == 3 && !strcmp(argv[1], "--branch"))
		return check_ref_format_branch(argv[2]);

	for (i = 1; i < argc && argv[i][0] == '-'; i++) {
		if (!strcmp(argv[i], "--normalize") || !strcmp(argv[i], "--print"))
			normalize = 1;
		else if (!strcmp(argv[i], "--allow-onelevel"))
			flags |= REFNAME_ALLOW_ONELEVEL;
		else if (!strcmp(argv[i], "--no-allow-onelevel"))
			flags &= ~REFNAME_ALLOW_ONELEVEL;
		else if (!strcmp(argv[i], "--refspec-pattern"))
			flags |= REFNAME_REFSPEC_PATTERN;
		else
			usage(builtin_check_ref_format_usage);
	}
	if (! (i == argc - 1))
		usage(builtin_check_ref_format_usage);

	refname = argv[i];
	if (normalize)
		refname = collapse_slashes(refname);
	if (check_refname_format(refname, flags))
		return 1;
	if (normalize)
		printf("%s\n", refname);

	return 0;
}