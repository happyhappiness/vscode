static int compare_paths(const struct combine_diff_path *one,
			  const struct diff_filespec *two)
{
	if (!S_ISDIR(one->mode) && !S_ISDIR(two->mode))
		return strcmp(one->path, two->path);

	return base_name_compare(one->path, strlen(one->path), one->mode,
				 two->path, strlen(two->path), two->mode);
}