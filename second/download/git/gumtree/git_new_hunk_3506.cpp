{
	/*
	 * The format of this string should be kept stable for compatibility
	 * with external projects that rely on the output of "git version".
	 */
	printf("git version %s\n", git_version_string);
	while (*++argv) {
		if (!strcmp(*argv, "--build-options")) {
			printf("sizeof-long: %d\n", (int)sizeof(long));
			/* NEEDSWORK: also save and output GIT-BUILD_OPTIONS? */
		}
	}
	return 0;
}

struct similar_ref_cb {
	const char *base_ref;
	struct string_list *similar_refs;
