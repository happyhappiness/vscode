static void check_attr(const char *prefix,
		       struct attr_check *check,
		       int collect_all,
		       const char *file)
{
	char *full_path =
		prefix_path(prefix, prefix ? strlen(prefix) : 0, file);

	if (collect_all) {
		git_all_attrs(full_path, check);
	} else {
		if (git_check_attr(full_path, check))
			die("git_check_attr died");
	}
	output_attr(check, file);

	free(full_path);
}