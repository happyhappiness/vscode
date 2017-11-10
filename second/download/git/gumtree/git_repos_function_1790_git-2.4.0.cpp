int ll_merge_marker_size(const char *path)
{
	static struct git_attr_check check;
	int marker_size = DEFAULT_CONFLICT_MARKER_SIZE;

	if (!check.attr)
		check.attr = git_attr("conflict-marker-size");
	if (!git_check_attr(path, 1, &check) && check.value) {
		marker_size = atoi(check.value);
		if (marker_size <= 0)
			marker_size = DEFAULT_CONFLICT_MARKER_SIZE;
	}
	return marker_size;
}