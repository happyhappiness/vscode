{
	/*
	 * The format of this string should be kept stable for compatibility
	 * with external projects that rely on the output of "git version".
	 */
	printf("git version %s\n", git_version_string);
	return 0;
}

struct similar_ref_cb {
	const char *base_ref;
	struct string_list *similar_refs;
