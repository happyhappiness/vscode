
	exit(1);
}

int cmd_version(int argc, const char **argv, const char *prefix)
{
	int build_options = 0;
	const char * const usage[] = {
		N_("git version [<options>]"),
		NULL
	};
	struct option options[] = {
		OPT_BOOL(0, "build-options", &build_options,
			 "also print build options"),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options, usage, 0);

	/*
	 * The format of this string should be kept stable for compatibility
	 * with external projects that rely on the output of "git version".
	 *
	 * Always show the version, even if other options are given.
	 */
	printf("git version %s\n", git_version_string);

	if (build_options) {
		printf("sizeof-long: %d\n", (int)sizeof(long));
		/* NEEDSWORK: also save and output GIT-BUILD_OPTIONS? */
	}
	return 0;
}

struct similar_ref_cb {
	const char *base_ref;
