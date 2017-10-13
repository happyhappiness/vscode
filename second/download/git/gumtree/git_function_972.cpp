static void check_attr(const char *prefix, int cnt,
	struct git_attr_check *check, const char *file)
{
	char *full_path =
		prefix_path(prefix, prefix ? strlen(prefix) : 0, file);
	if (check != NULL) {
		if (git_check_attr(full_path, cnt, check))
			die("git_check_attr died");
		output_attr(cnt, check, file);
	} else {
		if (git_all_attrs(full_path, &cnt, &check))
			die("git_all_attrs died");
		output_attr(cnt, check, file);
		free(check);
	}
	free(full_path);
}