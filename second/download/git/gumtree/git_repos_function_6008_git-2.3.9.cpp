int cmd_fetch__tool(int argc, const char **argv, const char *prefix)
{
	int verbose = 0;
	int force = 0;
	int sopt = 0;

	while (1 < argc) {
		const char *arg = argv[1];
		if (!strcmp("-v", arg))
			verbose = 1;
		else if (!strcmp("-f", arg))
			force = 1;
		else if (!strcmp("-s", arg))
			sopt = 1;
		else
			break;
		argc--;
		argv++;
	}

	if (argc <= 1)
		return error("Missing subcommand");

	if (!strcmp("append-fetch-head", argv[1])) {
		int result;
		FILE *fp;
		char *filename;

		if (argc != 8)
			return error("append-fetch-head takes 6 args");
		filename = git_path("FETCH_HEAD");
		fp = fopen(filename, "a");
		if (!fp)
			return error("cannot open %s: %s", filename, strerror(errno));
		result = append_fetch_head(fp, argv[2], argv[3],
					   argv[4], argv[5],
					   argv[6], !!argv[7][0],
					   verbose, force);
		fclose(fp);
		return result;
	}
	if (!strcmp("native-store", argv[1])) {
		int result;
		FILE *fp;
		char *filename;

		if (argc != 5)
			return error("fetch-native-store takes 3 args");
		filename = git_path("FETCH_HEAD");
		fp = fopen(filename, "a");
		if (!fp)
			return error("cannot open %s: %s", filename, strerror(errno));
		result = fetch_native_store(fp, argv[2], argv[3], argv[4],
					    verbose, force);
		fclose(fp);
		return result;
	}
	if (!strcmp("parse-reflist", argv[1])) {
		const char *reflist;
		if (argc != 3)
			return error("parse-reflist takes 1 arg");
		reflist = argv[2];
		if (!strcmp(reflist, "-"))
			reflist = get_stdin();
		return parse_reflist(reflist);
	}
	if (!strcmp("pick-rref", argv[1])) {
		const char *ls_remote_result;
		if (argc != 4)
			return error("pick-rref takes 2 args");
		ls_remote_result = argv[3];
		if (!strcmp(ls_remote_result, "-"))
			ls_remote_result = get_stdin();
		return pick_rref(sopt, argv[2], ls_remote_result);
	}
	if (!strcmp("expand-refs-wildcard", argv[1])) {
		const char *reflist;
		if (argc < 4)
			return error("expand-refs-wildcard takes at least 2 args");
		reflist = argv[2];
		if (!strcmp(reflist, "-"))
			reflist = get_stdin();
		return expand_refs_wildcard(reflist, argc - 3, argv + 3);
	}

	return error("Unknown subcommand: %s", argv[1]);
}