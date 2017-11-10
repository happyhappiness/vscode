int cmd_version(int argc, const char **argv, const char *prefix)
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